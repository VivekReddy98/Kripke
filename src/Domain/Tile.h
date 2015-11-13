#ifndef DOMAIN_TILE_H__
#define DOMAIN_TILE_H__

#include<RAJA/RAJA.hxx>


// Policy for no tiling
struct tile_none {};


// Policy to tile by given block size
template<int TileSize>
struct tile_fixed {};


// Policy to tile over IndexSet segments
struct tile_indexset {};


template<typename TI, typename BODY>
void forall_tile(tile_none, TI const &is, BODY const &body){
  body(is);
}


template<int TileSize, typename BODY>
void forall_tile(tile_fixed<TileSize>, RAJA::RangeSegment const &is, BODY const &body){
  // tile loop
  int i_begin = is.getBegin();
  int i_end = is.getEnd();
  for(int i0 = i_begin;i0 < i_end;i0 += TileSize){
  
    // Create a new tile
    int i1 = std::min(i0+TileSize, i_end);
    RAJA::RangeSegment is_tile(i0, i1);
      
    // Pass tile index set to body        
    body(is_tile);
  }  
}


template<typename BODY>
void forall_tile(tile_indexset, RAJA::IndexSet const &iset, BODY const &body){
     const int num_seg = iset.getNumSegments();

   for ( int isi = 0; isi < num_seg; ++isi ) {

      const RAJA::BaseSegment* iseg = iset.getSegment(isi);
      RAJA::SegmentType segtype = iseg->getType();

      switch ( segtype ) {

         case RAJA::_RangeSeg_ : {
            const RAJA::RangeSegment* tseg =
               static_cast<const RAJA::RangeSegment*>(iseg);
            
            // call body with segment
            body(*tseg);
            break;
         }

#if 0  // RDH RETHINK
         case _RangeStrideSeg_ : {
            const RangeStrideSegment* tseg =
               static_cast<const RangeStrideSegment*>(iseg); 
            forall(
               SEG_EXEC_POLICY_T(),
               tseg->getBegin(), tseg->getEnd(), tseg->getStride(),
               loop_body
            );
            break;
         }
#endif
/*
         case _ListSeg_ : {
            const ListSegment* tseg =
               static_cast<const ListSegment*>(iseg);
            forall(
               SEG_EXEC_POLICY_T(),
               tseg->getIndex(), tseg->getLength(), 
               loop_body
            );
            break;
         }
*/
         default : {
         }

      }  // switch on segment type

   } // iterate over segments of index set  
}


#endif
