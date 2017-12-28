/* -*- Mode: C; c-basic-offset:4 ; indent-tabs-mode:nil ; -*- */
/*
 *  (C) 2017 by Argonne National Laboratory.
 *      See COPYRIGHT in top-level directory.
 */

#include "mpiimpl.h"

#undef FUNCNAME
#undef FUNCNAME
#define FUNCNAME MPIR_Bcast_nb
#undef FCNAME
#define FCNAME MPL_QUOTE(FUNCNAME)
int MPIR_Bcast_nb(void *buffer, int count, MPI_Datatype datatype, int root, MPIR_Comm * comm_ptr,
                  MPIR_Errflag_t * errflag)
{
    int mpi_errno = MPI_SUCCESS;
    MPI_Request req;

    /* just call the nonblocking version and wait on it */
    mpi_errno = MPID_Ibcast(buffer, count, datatype, root, comm_ptr, &req);
    if (mpi_errno)
        MPIR_ERR_POP(mpi_errno);

    mpi_errno = MPIR_Wait_impl(&req, MPI_STATUS_IGNORE);
    if (mpi_errno)
        MPIR_ERR_POP(mpi_errno);

  fn_exit:
    return mpi_errno;
  fn_fail:
    goto fn_exit;
}