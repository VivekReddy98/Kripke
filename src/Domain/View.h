//AUTOGENERATED BY genView.py
  
#ifndef __DOMAIN_VIEW_H__
#define __DOMAIN_VIEW_H__

#include "Layout.h"


    template<typename DataType, typename Layout>
    struct View1d {
      typedef typename Layout::Permutation Permutation;
      typedef typename Layout::IndexI IndexI;

      Layout const layout;
      DataType *data;

      inline View1d(DataType *data_ptr, int ni):
        layout(ni),
        data(data_ptr)
      {}

      inline DataType &operator()(IndexI i) const {
        return data[convertIndex<int>(layout(i))];
      }
    };

    template<typename DataType, typename Layout>
    struct View2d {
      typedef typename Layout::Permutation Permutation;
      typedef typename Layout::IndexI IndexI;
      typedef typename Layout::IndexJ IndexJ;

      Layout const layout;
      DataType *data;

      inline View2d(DataType *data_ptr, int ni, int nj):
        layout(ni, nj),
        data(data_ptr)
      {}

      inline DataType &operator()(IndexI i, IndexJ j) const {
        return data[convertIndex<int>(layout(i, j))];
      }
    };

    template<typename DataType, typename Layout>
    struct View3d {
      typedef typename Layout::Permutation Permutation;
      typedef typename Layout::IndexI IndexI;
      typedef typename Layout::IndexJ IndexJ;
      typedef typename Layout::IndexK IndexK;

      Layout const layout;
      DataType *data;

      inline View3d(DataType *data_ptr, int ni, int nj, int nk):
        layout(ni, nj, nk),
        data(data_ptr)
      {}

      inline DataType &operator()(IndexI i, IndexJ j, IndexK k) const {
        return data[convertIndex<int>(layout(i, j, k))];
      }
    };

    template<typename DataType, typename Layout>
    struct View4d {
      typedef typename Layout::Permutation Permutation;
      typedef typename Layout::IndexI IndexI;
      typedef typename Layout::IndexJ IndexJ;
      typedef typename Layout::IndexK IndexK;
      typedef typename Layout::IndexL IndexL;

      Layout const layout;
      DataType *data;

      inline View4d(DataType *data_ptr, int ni, int nj, int nk, int nl):
        layout(ni, nj, nk, nl),
        data(data_ptr)
      {}

      inline DataType &operator()(IndexI i, IndexJ j, IndexK k, IndexL l) const {
        return data[convertIndex<int>(layout(i, j, k, l))];
      }
    };


  
#endif

