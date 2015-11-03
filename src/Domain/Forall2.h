//AUTOGENERATED BY genForallN.py
  
#ifndef __DOMAIN_FORALL2_H__
#define __DOMAIN_FORALL2_H__

#include<RAJA/RAJA.hxx>
#include<Domain/Tile.h>



/******************************************************************
 *  Policy base class, forall2()
 ******************************************************************/

    // Execute (Termintation-case for all policies)
    struct Forall2_Execute_Tag {};
    struct Forall2_Execute {
      typedef Forall2_Execute_Tag PolicyTag;
    };

    // Starting place for all forall2 policies
    // Identified each loops execution policy
    struct Forall2_Policy_Tag{};
    template<typename POL_I, typename POL_J, typename NEXT=Forall2_Execute>
    struct Forall2_Policy{
      typedef Forall2_Policy_Tag PolicyTag;
      typedef NEXT NextPolicy;
      typedef POL_I PolicyI;
	  typedef POL_J PolicyJ;
    };

    // Interchange loop order given the permutation
    struct Forall2_Permute_Tag{};
    template<typename LOOP_ORDER, typename NEXT=Forall2_Execute>
    struct Forall2_Permute {
      typedef Forall2_Permute_Tag PolicyTag;
      typedef NEXT NextPolicy;
      typedef LOOP_ORDER LoopOrder;
    };

    // Begin OpenMP Parallel Region
    struct Forall2_OMP_Parallel_Tag {};
    template<typename NEXT=Forall2_Execute>
    struct Forall2_OMP_Parallel {
      typedef Forall2_OMP_Parallel_Tag PolicyTag;
      typedef NEXT NextPolicy;
    };

    // Tiling Policy
    struct Forall2_Tile_Tag {};
    template<typename TILE_I, typename TILE_J, typename NEXT=Forall2_Execute>
    struct Forall2_Tile {
      typedef Forall2_Tile_Tag PolicyTag;
      typedef NEXT NextPolicy;
      typedef TILE_I TileI;
      typedef TILE_J TileJ;
    };


    // foreward declaration
    template<typename POLICY, typename PolicyI, typename PolicyJ, typename TI, typename TJ, typename BODY>
	RAJA_INLINE void forall2_policy(Forall2_Execute_Tag, TI const &is_i, TJ const &is_j, BODY const &body);

    template<typename POLICY, typename PolicyI, typename PolicyJ, typename TI, typename TJ, typename BODY>
	RAJA_INLINE void forall2_policy(Forall2_Permute_Tag, TI const &is_i, TJ const &is_j, BODY const &body);

    template<typename POLICY, typename PolicyI, typename PolicyJ, typename TI, typename TJ, typename BODY>
	RAJA_INLINE void forall2_policy(Forall2_OMP_Parallel_Tag, TI const &is_i, TJ const &is_j, BODY const &body);

    template<typename POLICY, typename PolicyI, typename PolicyJ, typename TI, typename TJ, typename BODY>
	RAJA_INLINE void forall2_policy(Forall2_Tile_Tag, TI const &is_i, TJ const &is_j, BODY const &body);


/******************************************************************
 *  Default Executor for forall2()
 ******************************************************************/

    template<typename POLICY_I, typename POLICY_J, typename TI, typename TJ>
    class Forall2Executor {
      public:  
        template<typename BODY>
        inline void operator()(TI const &is_i, TJ const &is_j, BODY const &body) const {
          RAJA::forall<POLICY_I>(is_i, RAJA_LAMBDA(int i){
            RAJA::forall<POLICY_J>(is_j, RAJA_LAMBDA(int j){
              body(i, j);
            });
          });
        }
    };


/******************************************************************
 *  OpenMP Auto-Collapsing Executors for forall2()
 ******************************************************************/

#ifdef _OPENMP

    // OpenMP Executor with collapse(2) for omp_parallel_for_exec
    template<>
    class Forall2Executor<RAJA::omp_parallel_for_exec, RAJA::omp_parallel_for_exec, RAJA::RangeSegment, RAJA::RangeSegment> {
      public:  
        template<typename BODY>
        inline void operator()(RAJA::RangeSegment const &is_i, RAJA::RangeSegment const &is_j, BODY const &body) const {
          int const i_start = is_i.getBegin();
          int const i_end   = is_i.getEnd();

          int const j_start = is_j.getBegin();
          int const j_end   = is_j.getEnd();

#pragma omp parallel for schedule(static) collapse(2)
          for(int i = i_start;i < i_end;++ i){
            for(int j = j_start;j < j_end;++ j){
              body(i, j);
          } } 
        }
    };

    // OpenMP Executor with collapse(2) for omp_for_nowait_exec
    template<>
    class Forall2Executor<RAJA::omp_for_nowait_exec, RAJA::omp_for_nowait_exec, RAJA::RangeSegment, RAJA::RangeSegment> {
      public:  
        template<typename BODY>
        inline void operator()(RAJA::RangeSegment const &is_i, RAJA::RangeSegment const &is_j, BODY const &body) const {
          int const i_start = is_i.getBegin();
          int const i_end   = is_i.getEnd();

          int const j_start = is_j.getBegin();
          int const j_end   = is_j.getEnd();

#pragma omp for schedule(static) collapse(2) nowait
          for(int i = i_start;i < i_end;++ i){
            for(int j = j_start;j < j_end;++ j){
              body(i, j);
          } } 
        }
    };


#endif // _OPENMP


/******************************************************************
 *  Permutations layer for forall2()
 ******************************************************************/

      template<typename POLICY, typename PolicyI, typename PolicyJ, typename TI, typename TJ, typename BODY>
      RAJA_INLINE void forall2_permute(PERM_IJ, TI const &is_i, TJ const &is_j, BODY const &body){
    	typedef typename POLICY::NextPolicy NextPolicy;
		typedef typename POLICY::NextPolicy::PolicyTag NextPolicyTag;

		forall2_policy<NextPolicy, PolicyI, PolicyJ, TI, TJ>(NextPolicyTag(), is_i, is_j,
	      [=](int i, int j){body(i,j);}
		);
      }

      template<typename POLICY, typename PolicyI, typename PolicyJ, typename TI, typename TJ, typename BODY>
      RAJA_INLINE void forall2_permute(PERM_JI, TI const &is_i, TJ const &is_j, BODY const &body){
		typedef typename POLICY::NextPolicy NextPolicy;
		typedef typename POLICY::NextPolicy::PolicyTag NextPolicyTag;

		forall2_policy<NextPolicy, PolicyJ, PolicyI, TJ, TI>(NextPolicyTag(), is_j, is_i,
		  [=](int j, int i){body(i,j);}
		);
      }




/******************************************************************
 *  forall2() Policy Layer, specializations for policy tags
 ******************************************************************/
  template<typename POLICY, typename PolicyI, typename PolicyJ, typename TI, typename TJ, typename BODY>
    RAJA_INLINE void forall2_policy(Forall2_Permute_Tag, TI const &is_i, TJ const &is_j, BODY const &body){
      // pull out loop ordering
	  typedef typename POLICY::LoopOrder L;

	  // call loop interchange specialization for L
	  forall2_permute<POLICY, PolicyI, PolicyJ, TI, TJ, BODY>(L(), is_i, is_j, body);
	}

    // OpenMP Parallel region
    template<typename POLICY, typename PolicyI, typename PolicyJ, typename TI, typename TJ, typename BODY>
	RAJA_INLINE void forall2_policy(Forall2_OMP_Parallel_Tag, TI const &is_i, TJ const &is_j, BODY const &body){
      typedef typename POLICY::NextPolicy NextPolicy;
	  typedef typename POLICY::NextPolicy::PolicyTag NextPolicyTag;

#ifdef _OPENMP
#pragma omp parallel
#endif
	  {
        // execute the next policy
        forall2_policy<NextPolicy, PolicyI, PolicyJ, TI, TJ, BODY>(NextPolicyTag(), is_i, is_j, body);
      }
	}

    template<typename POLICY, typename PolicyI, typename PolicyJ, typename TI, typename TJ, typename BODY>
    RAJA_INLINE void forall2_policy(Forall2_Execute_Tag, TI const &is_i, TJ const &is_j, BODY const &body){
	  Forall2Executor<PolicyJ, PolicyI, TJ, TI> exec;
	  exec(is_j, is_i, RAJA_LAMBDA(int j, int i){
	    body(i, j);
	  });
    }

    template<typename POLICY, typename PolicyI, typename PolicyJ, typename TI, typename TJ, typename BODY>
	RAJA_INLINE void forall2_policy(Forall2_Tile_Tag, TI const &is_i, TJ const &is_j, BODY const &body){
	  typedef typename POLICY::NextPolicy NextPolicy;
	  typedef typename POLICY::NextPolicy::PolicyTag NextPolicyTag;
	  typedef typename POLICY::TileI TileI;
	  typedef typename POLICY::TileJ TileJ;

	  // execute the next policy
	  forall_tile(TileI(), is_i, [=](auto is_ii){
		forall_tile(TileJ(), is_j, [=](auto is_jj){
		  forall2_policy<NextPolicy, PolicyI, PolicyJ>(NextPolicyTag(), is_ii, is_jj, body);
		});
	  });
	}


/******************************************************************
 *  forall2(), User Interface, non-reentrant
 ******************************************************************/

    template<typename POLICY, typename IdxI=int, typename IdxJ=int, typename TI, typename TJ, typename BODY>
    RAJA_INLINE void forall2(TI const &is_i, TJ const &is_j, BODY const &body){
      typedef typename POLICY::NextPolicy NextPolicy;
	  typedef typename POLICY::NextPolicy::PolicyTag NextPolicyTag;

      // extract each loop's execution policy
      typedef typename POLICY::PolicyI PolicyI;
      typedef typename POLICY::PolicyJ PolicyJ;

      // call "policy" layer, wrapping with strongly-typed indices
      forall2_policy<NextPolicy, PolicyI, PolicyJ, TI, TJ>(NextPolicyTag(), is_i, is_j,
        [=](int i, int j){
    	  // call body with specified index types
          body(IdxI(i), IdxJ(j));
        }
      );


    }


  
#endif

