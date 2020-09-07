// Copyright 2008-2016 Conrad Sanderson (http://conradsanderson.id.au)
// Copyright 2008-2016 National ICT Australia (NICTA)
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// ------------------------------------------------------------------------


//! \addtogroup op_max
//! @{


class op_max
  : public traits_op_xvec
  {
  public:
  
  // 
  // dense matrices
  
  template<typename T1>
  inline static void apply(Mat<typename T1::elem_type>& out, const Op<T1,op_max>& in);
  
  template<typename eT>
  inline static void apply_noalias(Mat<eT>& out, const Mat<eT>& X, const uword dim, const typename arma_not_cx<eT>::result* junk = 0);
  
  template<typename eT>
  inline static void apply_noalias(Mat<eT>& out, const Mat<eT>& X, const uword dim, const typename arma_cx_only<eT>::result* junk = 0);
  
  
  // 
  // cubes
  
  template<typename T1>
  inline static void apply(Cube<typename T1::elem_type>& out, const OpCube<T1,op_max>& in);
  
  template<typename eT>
  inline static void apply_noalias(Cube<eT>& out, const Cube<eT>& X, const uword dim, const typename arma_not_cx<eT>::result* junk = 0);
  
  template<typename eT>
  inline static void apply_noalias(Cube<eT>& out, const Cube<eT>& X, const uword dim, const typename arma_cx_only<eT>::result* junk = 0);
  
  
  //
  // for non-complex numbers
  
  template<typename eT>
  inline static eT direct_max(const eT* const X, const uword N);
  
  template<typename eT>
  inline static eT direct_max(const eT* const X, const uword N, uword& index_of_max_val);
  
  template<typename eT>
  inline static eT direct_max(const Mat<eT>& X, const uword row);
  
  template<typename eT>
  inline static eT max(const subview<eT>& X);
  
  template<typename T1>
  inline static typename arma_not_cx<typename T1::elem_type>::result max(const Base<typename T1::elem_type, T1>& X);
  
  template<typename T1>
  inline static typename arma_not_cx<typename T1::elem_type>::result max(const BaseCube<typename T1::elem_type, T1>& X);
  
  template<typename T1>
  inline static typename arma_not_cx<typename T1::elem_type>::result max_with_index(const Proxy<T1>& P, uword& index_of_max_val);
  
  template<typename T1>
  inline static typename arma_not_cx<typename T1::elem_type>::result max_with_index(const ProxyCube<T1>& P, uword& index_of_max_val);
  

  //
  // for complex numbers
  
  template<typename T>
  inline static std::complex<T> direct_max(const std::complex<T>* const X, const uword n_elem);
  
  template<typename T>
  inline static std::complex<T> direct_max(const std::complex<T>* const X, const uword n_elem, uword& index_of_max_val);
  
  template<typename T>
  inline static std::complex<T> direct_max(const Mat< std::complex<T> >& X, const uword row);
  
  template<typename T>
  inline static std::complex<T> max(const subview< std::complex<T> >& X);
  
  template<typename T1>
  inline static typename arma_cx_only<typename T1::elem_type>::result max(const Base<typename T1::elem_type, T1>& X);
  
  template<typename T1>
  inline static typename arma_cx_only<typename T1::elem_type>::result max(const BaseCube<typename T1::elem_type, T1>& X);
  
  template<typename T1>
  inline static typename arma_cx_only<typename T1::elem_type>::result max_with_index(const Proxy<T1>& P, uword& index_of_max_val);
  
  template<typename T1>
  inline static typename arma_cx_only<typename T1::elem_type>::result max_with_index(const ProxyCube<T1>& P, uword& index_of_max_val);
  };



//! @}
