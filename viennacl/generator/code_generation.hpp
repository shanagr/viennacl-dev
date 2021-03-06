#ifndef VIENNACL_GENERATOR_CODE_GENERATION_HPP
#define VIENNACL_GENERATOR_CODE_GENERATION_HPP

#include <cstdio>
#include <cstdlib>
#include <algorithm>

#include <typeinfo>

#include "viennacl/ocl/infos.hpp"


#include "viennacl/generator/templates/gemm.hpp"
#include "viennacl/generator/templates/gemv.hpp"
#include "viennacl/generator/templates/inner_product.hpp"
#include "viennacl/generator/templates/saxpy.hpp"

#include "viennacl/generator/symbolic_types.hpp"
#include "viennacl/generator/utils.hpp"
#include "viennacl/generator/builtin_database.hpp"
#include "viennacl/tools/shared_ptr.hpp"

namespace viennacl{

    namespace generator{


        template<class ArgumentsT>
        void set_arguments(viennacl::ocl::kernel & k, ArgumentsT const & args){
            unsigned int counter=0;
            for(typename ArgumentsT::const_iterator iit = args.begin(); iit != args.end() ; ++iit){
                (*iit)->enqueue(counter,k);
            }
        }




        namespace code_generation{

            class kernel_infos_t{
            public:
                kernel_infos_t(symbolic_expression_tree_base *op, optimization_profile* prof) : optimization_profile_(prof){ trees_.push_back(op); }
                kernel_infos_t(symbolic_expression_tree_base *op, viennacl::tools::shared_ptr<optimization_profile> prof) : optimization_profile_(prof){ trees_.push_back(op); }
                std::list<symbolic_expression_tree_base*> & trees(){ return trees_; }
                code_generation::optimization_profile* profile() { return optimization_profile_.get(); }
                void config_nd_range(viennacl::ocl::kernel & k) const{
                    symbolic_binary_expression_tree_infos_base * t = dynamic_cast<symbolic_binary_expression_tree_infos_base *>(trees_.front());
                    optimization_profile_->config_nd_range(k,&t->lhs());
                }
                void enqueue(viennacl::ocl::kernel & k){
                    unsigned int garbage = 0;
                    for(std::vector<tools::shared_ptr<symbolic_kernel_argument> >::iterator it=arguments_.begin(); it!=arguments_.end();++it){
                        (*it)->enqueue(garbage,k);
                    }
                }
                void init_arguments(){
                    for(std::list<symbolic_expression_tree_base*>::iterator it = trees_.begin() ; it!= trees_.end() ; ++it){
                        (*it)->get_kernel_arguments(arguments_);
                    }
                }
                void fill_arguments(utils::kernel_generation_stream & kss){
                    for(std::vector<tools::shared_ptr<symbolic_kernel_argument> >::iterator it=arguments_.begin(); it!=arguments_.end();++it){
                        if(it!=arguments_.begin()) kss << ',';
                        kss << (*it)->repr() << std::endl ;
                    }
                }

            private:
                std::list<symbolic_expression_tree_base*> trees_;
                std::vector<tools::shared_ptr<symbolic_kernel_argument> > arguments_;
                viennacl::tools::shared_ptr<code_generation::optimization_profile> optimization_profile_;
            };



            class kernel_generator{
            private:

                void generate_headers(){
                    kss_ << "__kernel void " + kernel_name_ + "(";
                    kernel_infos_.init_arguments();
                    kernel_infos_.fill_arguments(kss_);
                    kss_ << ")" << std::endl;
                }

                void generate_sources(){
                    kss_<<"{"<< std::endl;
                    kss_.inc_tab();
                    std::list<symbolic_binary_vector_expression_base *> vec_exprs = utils::cast<symbolic_binary_vector_expression_base>(kernel_infos_.trees());
                    std::list<symbolic_binary_matrix_expression_base *> mat_exprs = utils::cast<symbolic_binary_matrix_expression_base>(kernel_infos_.trees());
                    std::list<symbolic_binary_scalar_expression_base *> scal_exprs = utils::cast<symbolic_binary_scalar_expression_base>(kernel_infos_.trees());
                    code_generation::generator * gen;
                    if(saxpy::profile* p = dynamic_cast<saxpy::profile*>(kernel_infos_.profile())){
                        gen = new saxpy::generator(vec_exprs,scal_exprs,mat_exprs,p);
                    }
                    else if(gemm::profile* p = dynamic_cast<gemm::profile*>(kernel_infos_.profile())){
                        gen = new gemm::generator(mat_exprs,p);
                    }
                    else if(inner_product::profile* p = dynamic_cast<inner_product::profile*>(kernel_infos_.profile())){
                        gen = new inner_product::generator(scal_exprs,p);
                    }
                    else if(gemv::profile * p = dynamic_cast<gemv::profile*>(kernel_infos_.profile())){
                        gen = new gemv::generator(vec_exprs,p);
                    }
                    assert(gen && "KERNEL TYPE NOT RECOGNIZED");
                    (*gen)(kss_);
                    delete gen;
                    kss_.dec_tab();
                    kss_<<"}"<< std::endl;
                }

            public:
                kernel_generator(kernel_infos_t & kernel_infos
                                 , std::string const & kernel_name
                                 , utils::kernel_generation_stream & kss) : kernel_infos_(kernel_infos)
                                                                     , kernel_name_(kernel_name)
                                                                     , kss_(kss){

                }

                void generate(){
                    generate_headers();
                    generate_sources();
                }


            private:
                kernel_infos_t & kernel_infos_;
                std::string kernel_name_;
                utils::kernel_generation_stream & kss_;
            };



            class operations_manager{
            public:
                class barrier{

                };

            private:
                typedef std::list<viennacl::tools::shared_ptr<symbolic_expression_tree_base> > operations_t;

                template<class T>
                kernel_infos_t create_infos(symbolic_expression_tree_base* op){
                    std::map<std::string, viennacl::tools::shared_ptr<optimization_profile> >::iterator ito = overriden_models_.find(typeid(T).name());
                    if(ito!=overriden_models_.end()) return kernel_infos_t(op,ito->second);
                    //Lookup in the built-in database
                    cl_device_id id = viennacl::ocl::current_device().id();
                    builtin_database_t::iterator it = builtin_dabase.find(std::make_pair(ocl::info<CL_DEVICE_VENDOR_ID>(id), ocl::info<CL_DEVICE_TYPE>(id)));
                    if(it!=builtin_dabase.end()){
                        builtin_database_t::value_type::second_type::iterator it2 = it->second.find(op->simplified_repr());
                        if(it2!=it->second.end())  return kernel_infos_t(op,it2->second);
                    }
                    return kernel_infos_t(op, new T());

                }

                template<class T>
                T const & add_operation(symbolic_expression_tree_base* p){
                    if(kernels_list_.empty()) kernels_list_.push_back(create_infos<T>(p));
                    else{
                        if(dynamic_cast<T*>(kernels_list_.back().profile())) kernels_list_.back().trees().push_back(p);
                        else kernels_list_.push_back(create_infos<T>(p));
                    }
                    return * static_cast<T*>(kernels_list_.back().profile());
                }

                void init(){
                    if(!kernels_list_.empty()) return;
                    for(typename operations_t::const_iterator it = operations_.begin() ; it!=operations_.end() ; ++it){
                        symbolic_expression_tree_base* ptr = it->get();
                        if(symbolic_binary_matrix_expression_base* p = dynamic_cast<symbolic_binary_matrix_expression_base*>(ptr)){
                            if(count_type<symbolic_matrix_matrix_product_base>(p)) add_operation<gemm::profile>(p);
                            else add_operation<saxpy::profile>(p);
                        }
                        else if(symbolic_binary_vector_expression_base* p = dynamic_cast<symbolic_binary_vector_expression_base*>(ptr)){
                            if(count_type<symbolic_matrix_vector_product_base>(p)) add_operation<gemv::profile>(p);
                            else add_operation<saxpy::profile>(p);
                        }
                        else if(symbolic_binary_scalar_expression_base* p = dynamic_cast<symbolic_binary_scalar_expression_base*>(ptr)){
                            if(count_type<symbolic_inner_product_base>(p)){
                                inner_product::profile const & prof =add_operation<inner_product::profile>(p);
                                kernels_list_.push_back(kernel_infos_t(p, new inner_product::profile(prof.vectorization(),prof.num_groups(),1)));
                            }
                            else{
                                add_operation<saxpy::profile>(p);
                            }
                        }
                         else{
                            assert(false && "UNRECOGNIZED SCALARTYPE");
                        }
                        ptr->bind(shared_infos_, kernels_list_.back().profile());
                    }
                }

            public:

                operations_manager(){

                }

                template<class T>
                void override_model(T const & o){
                    overriden_models_[typeid(T).name()].reset(new T(o));
                }

                template<class T>
                void add(T const & op){
                    operations_.push_back(viennacl::tools::shared_ptr<symbolic_expression_tree_base>(new T(op)));
                }

                void flush(){
                    operations_.clear();
                }

                std::list<kernel_infos_t> get_kernels_list(){
                    init();
                    return kernels_list_;
                }

                std::string repr(){
                    init();
                    std::string res;
                    for(std::list<kernel_infos_t>::iterator it = kernels_list_.begin() ; it !=kernels_list_.end() ; ++it){
                        for(std::list<symbolic_expression_tree_base*>::iterator iit = it->trees().begin() ; iit != it->trees().end() ; ++iit){
                            res += (*iit)->repr();
                        }
                        res+=' ' + it->profile()->repr();
                    }
                    return res;
                }

                std::string get_source_code( std::map<std::string, kernel_infos_t> & kernels_infos){
                    init();

                    std::ostringstream oss;
                    utils::kernel_generation_stream kss(oss);
                    kss << "#if defined(cl_khr_fp64)\n";
                    kss <<  "#  pragma OPENCL EXTENSION cl_khr_fp64: enable\n";
                    kss <<  "#elif defined(cl_amd_fp64)\n";
                    kss <<  "#  pragma OPENCL EXTENSION cl_amd_fp64: enable\n";
                    kss <<  "#endif\n";

                    for(std::list<kernel_infos_t>::iterator it = kernels_list_.begin() ; it !=kernels_list_.end() ; ++it){
                        std::string name("_k"+utils::to_string(std::distance(kernels_list_.begin(),it)));
                        kernel_infos_t & infos = kernels_infos.insert(std::make_pair(name,*it)).first->second;
                        kss <<  "__attribute__((reqd_work_group_size(" << infos.profile()->local_work_size().first
                                                                        << "," << infos.profile()->local_work_size().second
                                                                        << ",1)))" << std::endl;
                        code_generation::kernel_generator kg(infos,name,kss);
                        kg.generate() ;
                    }
                    return oss.str();
                }

            private:
                operations_t operations_;
                std::map<std::string, viennacl::tools::shared_ptr<optimization_profile> > overriden_models_;
                std::list<kernel_infos_t> kernels_list_;
                std::vector< std::pair<symbolic_datastructure *, tools::shared_ptr<shared_symbolic_infos_t> > > shared_infos_;
            };

        }


    }

}
#endif // KERNEL_GENERATOR_FRONTEND_HPP
