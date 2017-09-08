/*
 * RedirFS: Redirecting File System
 *
 * Copyright 2017 Slava Imameev
 * All rights reserved.
 *
 * This file is part of RedirFS.
 *
 * RedirFS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RedirFS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with RedirFS. If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _RFS_HOOKED_OPS_H
#define _RFS_HOOKED_OPS_H

#include "rfs_object.h"

struct rfs_file;
  
#define RFS_OPS_INSERTED (1)
#define RFS_OPS_REMOVED  (1<<1)
#define RFS_OPS_FILE     (1<<2)

struct rfs_hoperations {

#ifdef RFS_DBG
    #define RFS_HOPERATIONS_SIGNATURE 0xABCD0004
    uint32_t            signature;
#endif /* RFS_DBG */

    struct rfs_object   rfs_object;

    /*
     * a relaxed counter of references
     * can drop to zero and raise again
     */
    atomic_t            keep_alive;

    /*
    * RFS_OPS_* flags
    */
    unsigned int        flags;

    /* a pointer to the old operations */
    union {
        const struct file_operations    *f_op; /* referenced */
    } old;

    /*
     * the space for the new operations structure is 
     * normally allocated just after the rfs_hoperations
     */
    union {
        struct file_operations          *f_op;
    } new;
};

/*---------------------------------------------------------------------------*/

void
rfs_keep_operations(
    struct rfs_hoperations* rfs_hoperations);

void
rfs_unkeep_operations(
    struct rfs_hoperations* rfs_hoperations);

/*---------------------------------------------------------------------------*/

struct rfs_hoperations*
rfs_create_file_ops(
    struct rfs_file     *rfile);

/*---------------------------------------------------------------------------*/
#endif /* _RFS_HOOKED_OPS_H */