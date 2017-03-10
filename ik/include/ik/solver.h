#ifndef IK_SOLVER_H
#define IK_SOLVER_H

#include "ik/gen/config.h"
#include "ik/pstdint.h"
#include "ik/ordered_vector.h"
#include "ik/vec3.h"
#include "ik/quat.h"

C_HEADER_BEGIN

struct ik_effector_t;
struct log_t;
struct ik_node_t;
struct ik_solver_t;

typedef void (*ik_solver_destroy_func)(struct ik_solver_t*);
typedef int (*ik_solver_solve_func)(struct ik_solver_t*);
typedef int (*ik_solver_rebuild_data_func)(struct ik_solver_t*);

typedef void (*ik_solver_apply_constraint_cb_func)(struct ik_node_t*);
typedef void (*ik_solver_apply_result_cb_func)(struct ik_node_t*, struct vec3_t, struct quat_t);

enum algorithm_e
{
    ALGORITHM_FABRIK,
    ALGORITHM_JACOBIAN_INVERSE,
    ALGORITHM_JACOBIAN_TRANSPOSE
};

/*!
 * @brief This is a base struct for all solvers.
 */
#define SOLVER_DATA_HEAD                                             \
    ik_solver_apply_constraint_cb_func apply_constraint;             \
    ik_solver_apply_result_cb_func     apply_result;                 \
                                                                     \
    int32_t                            max_iterations;               \
    float                              tolerance;                    \
                                                                     \
    /* Derived structure callbacks */                                \
    ik_solver_destroy_func             destroy;                      \
    ik_solver_solve_func               solve;                        \
    ik_solver_rebuild_data_func        rebuild_data;                 \
                                                                     \
    struct ordered_vector_t            effector_nodes_list;          \
                                                                     \
    struct ik_node_t* tree;
struct ik_solver_t
{
    SOLVER_DATA_HEAD
};

IK_PUBLIC_API struct ik_solver_t*
ik_solver_create(enum algorithm_e algorithm);

IK_PUBLIC_API void
ik_solver_destroy(struct ik_solver_t* solver);

IK_PUBLIC_API void
ik_solver_set_tree(struct ik_solver_t* solver, struct ik_node_t* root);

IK_PUBLIC_API int
ik_solver_rebuild_data(struct ik_solver_t* solver);

IK_PUBLIC_API int
ik_solver_solve(struct ik_solver_t* solver);

C_HEADER_END

#endif /* IK_SOLVER_H */
