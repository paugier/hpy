// this is the smallest flag which we can use while still keeping the types as
// signed 32 bit ints
#define HPy_SLOT 0x40000000

// hpy-specific value (not used by CPython)
#define HPy_meth (1 | HPy_SLOT)

/* These magic numbers are the same as CPython, plus an HPy-specific flag */
#define HPy_mp_ass_subscript (3 | HPy_SLOT)
#define HPy_mp_length (4 | HPy_SLOT)
#define HPy_mp_subscript (5 | HPy_SLOT)
#define HPy_nb_absolute (6 | HPy_SLOT)
#define HPy_nb_add (7 | HPy_SLOT)
#define HPy_nb_and (8 | HPy_SLOT)
#define HPy_nb_bool (9 | HPy_SLOT)
#define HPy_nb_divmod (10 | HPy_SLOT)
#define HPy_nb_float (11 | HPy_SLOT)
#define HPy_nb_floor_divide (12 | HPy_SLOT)
#define HPy_nb_index (13 | HPy_SLOT)
#define HPy_nb_inplace_add (14 | HPy_SLOT)
#define HPy_nb_inplace_and (15 | HPy_SLOT)
#define HPy_nb_inplace_floor_divide (16 | HPy_SLOT)
#define HPy_nb_inplace_lshift (17 | HPy_SLOT)
#define HPy_nb_inplace_multiply (18 | HPy_SLOT)
#define HPy_nb_inplace_or (19 | HPy_SLOT)
#define HPy_nb_inplace_power (20 | HPy_SLOT)
#define HPy_nb_inplace_remainder (21 | HPy_SLOT)
#define HPy_nb_inplace_rshift (22 | HPy_SLOT)
#define HPy_nb_inplace_subtract (23 | HPy_SLOT)
#define HPy_nb_inplace_true_divide (24 | HPy_SLOT)
#define HPy_nb_inplace_xor (25 | HPy_SLOT)
#define HPy_nb_int (26 | HPy_SLOT)
#define HPy_nb_invert (27 | HPy_SLOT)
#define HPy_nb_lshift (28 | HPy_SLOT)
#define HPy_nb_multiply (29 | HPy_SLOT)
#define HPy_nb_negative (30 | HPy_SLOT)
#define HPy_nb_or (31 | HPy_SLOT)
#define HPy_nb_positive (32 | HPy_SLOT)
#define HPy_nb_power (33 | HPy_SLOT)
#define HPy_nb_remainder (34 | HPy_SLOT)
#define HPy_nb_rshift (35 | HPy_SLOT)
#define HPy_nb_subtract (36 | HPy_SLOT)
#define HPy_nb_true_divide (37 | HPy_SLOT)
#define HPy_nb_xor (38 | HPy_SLOT)
#define HPy_sq_ass_item (39 | HPy_SLOT)
#define HPy_sq_concat (40 | HPy_SLOT)
#define HPy_sq_contains (41 | HPy_SLOT)
#define HPy_sq_inplace_concat (42 | HPy_SLOT)
#define HPy_sq_inplace_repeat (43 | HPy_SLOT)
#define HPy_sq_item (44 | HPy_SLOT)
#define HPy_sq_length (45 | HPy_SLOT)
#define HPy_sq_repeat (46 | HPy_SLOT)
#define HPy_tp_alloc (47 | HPy_SLOT)
#define HPy_tp_base (48 | HPy_SLOT)
#define HPy_tp_bases (49 | HPy_SLOT)
#define HPy_tp_call (50 | HPy_SLOT)
#define HPy_tp_clear (51 | HPy_SLOT)
#define HPy_tp_dealloc (52 | HPy_SLOT)
#define HPy_tp_del (53 | HPy_SLOT)
#define HPy_tp_descr_get (54 | HPy_SLOT)
#define HPy_tp_descr_set (55 | HPy_SLOT)
#define HPy_tp_doc (56 | HPy_SLOT)
#define HPy_tp_getattr (57 | HPy_SLOT)
#define HPy_tp_getattro (58 | HPy_SLOT)
#define HPy_tp_hash (59 | HPy_SLOT)
#define HPy_tp_init (60 | HPy_SLOT)
#define HPy_tp_is_gc (61 | HPy_SLOT)
#define HPy_tp_iter (62 | HPy_SLOT)
#define HPy_tp_iternext (63 | HPy_SLOT)
#define HPy_tp_methods (64 | HPy_SLOT)
#define HPy_tp_new (65 | HPy_SLOT)
#define HPy_tp_repr (66 | HPy_SLOT)
#define HPy_tp_richcompare (67 | HPy_SLOT)
#define HPy_tp_setattr (68 | HPy_SLOT)
#define HPy_tp_setattro (69 | HPy_SLOT)
#define HPy_tp_str (70 | HPy_SLOT)
#define HPy_tp_traverse (71 | HPy_SLOT)
#define HPy_tp_members (72 | HPy_SLOT)
#define HPy_tp_getset (73 | HPy_SLOT)
#define HPy_tp_free (74 | HPy_SLOT)
#define HPy_nb_matrix_multiply (75 | HPy_SLOT)
#define HPy_nb_inplace_matrix_multiply (76 | HPy_SLOT)
#define HPy_am_await (77 | HPy_SLOT)
#define HPy_am_aiter (78 | HPy_SLOT)
#define HPy_am_anext (79 | HPy_SLOT)
/* New in 3.5 */
#define HPy_tp_finalize (80 | HPy_SLOT)
