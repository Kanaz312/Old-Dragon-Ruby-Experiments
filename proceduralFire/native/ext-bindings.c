#include <mruby.h>
#include <string.h>
#include <assert.h>
#include <mruby/string.h>
#include <mruby/data.h>
#include <dragonruby.h>
#include "app\ext.h"

// MRuby `typedef`s mrb_int in the mruby/value.h
// Then `#define`s mrb_int in mruby.h
// We need to undo the macro and avoid it's usage
// FIXME: I'm surely doing something wrong
#ifdef mrb_int
#undef mrb_int
#endif

void *(*drb_symbol_lookup)(const char *sym) = NULL;

static void (*drb_free_foreign_object_f)(mrb_state *, void *);
static struct RClass *(*mrb_module_get_f)(mrb_state *, const char *);
static mrb_int (*mrb_get_args_f)(mrb_state *, mrb_args_format, ...);
static struct RClass *(*mrb_module_get_under_f)(mrb_state *, struct RClass *, const char *);
static struct RClass *(*mrb_class_get_under_f)(mrb_state *, struct RClass *, const char *);
static struct RClass *(*mrb_define_module_under_f)(mrb_state *, struct RClass *, const char *);
static void (*mrb_define_module_function_f)(mrb_state *, struct RClass *, const char *, mrb_func_t, mrb_aspec);
static struct RClass *(*mrb_define_class_under_f)(mrb_state *, struct RClass *, const char *, struct RClass *);
static void (*mrb_define_method_f)(mrb_state *, struct RClass *, const char *, mrb_func_t, mrb_aspec);
static void (*mrb_define_class_method_f)(mrb_state *, struct RClass *, const char *, mrb_func_t, mrb_aspec);
static struct RData *(*mrb_data_object_alloc_f)(mrb_state *, struct RClass *, void *, const mrb_data_type *);
static mrb_value (*mrb_str_new_cstr_f)(mrb_state *, const char *);
static void (*mrb_raise_f)(mrb_state *, struct RClass *, const char *);
static struct RClass *(*mrb_exc_get_f)(mrb_state *, const char *);
static void drb_free_foreign_object_indirect(mrb_state *state, void *pointer) {
    drb_free_foreign_object_f(state, pointer);
}
struct drb_foreign_object_ZTSPd {
    drb_foreign_object_kind kind;
    double *value;
    int should_free;
};
static mrb_data_type ForeignObjectType_ZTSPd = {"double*", drb_free_foreign_object_indirect};
static double *drb_ffi__ZTSPd_FromRuby(mrb_state *state, mrb_value self) {
    if (mrb_nil_p(self))
        return 0;
    return ((struct drb_foreign_object_ZTSPd *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTSPd_ToRuby(mrb_state *state, double *value) {
    struct drb_foreign_object_ZTSPd *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSPd));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_pointer;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "RE");
    struct RClass *klass = mrb_class_get_under_f(state, module, "DoublePointer");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTSPd);
    return mrb_obj_value(rdata);
}
static int drb_ffi__ZTSi_FromRuby(mrb_state *state, mrb_value self) {
    return mrb_fixnum(self);
}
static mrb_value drb_ffi__ZTSi_ToRuby(mrb_state *state, int value) {
    return mrb_fixnum_value(value);
}
struct drb_foreign_object_ZTSPj {
    drb_foreign_object_kind kind;
    Uint32 *value;
    int should_free;
};
static mrb_data_type ForeignObjectType_ZTSPj = {"unsigned int*", drb_free_foreign_object_indirect};
static Uint32 *drb_ffi__ZTSPj_FromRuby(mrb_state *state, mrb_value self) {
    if (mrb_nil_p(self))
        return 0;
    return ((struct drb_foreign_object_ZTSPj *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTSPj_ToRuby(mrb_state *state, Uint32 *value) {
    struct drb_foreign_object_ZTSPj *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSPj));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_pointer;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "RE");
    struct RClass *klass = mrb_class_get_under_f(state, module, "Unsigned_intPointer");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTSPj);
    return mrb_obj_value(rdata);
}
struct drb_foreign_object_ZTSPv {
    drb_foreign_object_kind kind;
    void *value;
    int should_free;
};
static mrb_data_type ForeignObjectType_ZTSPv = {"void*", drb_free_foreign_object_indirect};
static void *drb_ffi__ZTSPv_FromRuby(mrb_state *state, mrb_value self) {
    if (mrb_nil_p(self))
        return 0;
    return ((struct drb_foreign_object_ZTSPv *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTSPv_ToRuby(mrb_state *state, void *value) {
    struct drb_foreign_object_ZTSPv *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSPv));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_pointer;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "RE");
    struct RClass *klass = mrb_class_get_under_f(state, module, "VoidPointer");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTSPv);
    return mrb_obj_value(rdata);
}
static unsigned int drb_ffi__ZTSj_FromRuby(mrb_state *state, mrb_value self) {
    return mrb_fixnum(self);
}
static mrb_value drb_ffi__ZTSj_ToRuby(mrb_state *state, unsigned int value) {
    return mrb_fixnum_value(value);
}
static double drb_ffi__ZTSd_FromRuby(mrb_state *state, mrb_value self) {
    return mrb_float(self);
}
static mrb_value drb_ffi__ZTSd_ToRuby(mrb_state *state, double value) {
    return mrb_float_value(state, value);
}
static mrb_value drb_ffi__ZTSPd_New(mrb_state *mrb, mrb_value self) {
    struct drb_foreign_object_ZTSPd *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSPd));
    ptr->kind = drb_foreign_object_kind_pointer;
    ptr->value = calloc(1, sizeof(double));
    ptr->should_free = 1;
    struct RClass *FFI = mrb_module_get_f(mrb, "FFI");
    struct RClass *module = mrb_module_get_under_f(mrb, FFI, "RE");
    struct RClass *klass = mrb_class_get_under_f(mrb, module, "DoublePointer");
    struct RData *rdata = mrb_data_object_alloc_f(mrb, klass, ptr, &ForeignObjectType_ZTSPd);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTSPd_GetValue(mrb_state *mrb, mrb_value value) {
    return drb_ffi__ZTSd_ToRuby(mrb, *drb_ffi__ZTSPd_FromRuby(mrb, value));
}
static mrb_value drb_ffi__ZTSPd_IsNil(mrb_state *state, mrb_value self) {
    if (drb_ffi__ZTSPd_FromRuby(state, self) == 0)
        return mrb_true_value();
    else
        return mrb_false_value();
}
static mrb_value drb_ffi__ZTSPd_GetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    return drb_ffi__ZTSd_ToRuby(mrb, drb_ffi__ZTSPd_FromRuby(mrb, self)[index]);
}
static mrb_value drb_ffi__ZTSPd_SetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    double new_value = drb_ffi__ZTSd_FromRuby(mrb, args[1]);
    drb_ffi__ZTSPd_FromRuby(mrb, self)[index] = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTSPj_New(mrb_state *mrb, mrb_value self) {
    struct drb_foreign_object_ZTSPj *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSPj));
    ptr->kind = drb_foreign_object_kind_pointer;
    ptr->value = calloc(1, sizeof(Uint32));
    ptr->should_free = 1;
    struct RClass *FFI = mrb_module_get_f(mrb, "FFI");
    struct RClass *module = mrb_module_get_under_f(mrb, FFI, "RE");
    struct RClass *klass = mrb_class_get_under_f(mrb, module, "Unsigned_intPointer");
    struct RData *rdata = mrb_data_object_alloc_f(mrb, klass, ptr, &ForeignObjectType_ZTSPj);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTSPj_GetValue(mrb_state *mrb, mrb_value value) {
    return drb_ffi__ZTSj_ToRuby(mrb, *drb_ffi__ZTSPj_FromRuby(mrb, value));
}
static mrb_value drb_ffi__ZTSPj_IsNil(mrb_state *state, mrb_value self) {
    if (drb_ffi__ZTSPj_FromRuby(state, self) == 0)
        return mrb_true_value();
    else
        return mrb_false_value();
}
static mrb_value drb_ffi__ZTSPj_GetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    return drb_ffi__ZTSj_ToRuby(mrb, drb_ffi__ZTSPj_FromRuby(mrb, self)[index]);
}
static mrb_value drb_ffi__ZTSPj_SetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    Uint32 new_value = drb_ffi__ZTSj_FromRuby(mrb, args[1]);
    drb_ffi__ZTSPj_FromRuby(mrb, self)[index] = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi_makeNoiseArr_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    int w_0 = drb_ffi__ZTSi_FromRuby(state, args[0]);
    int h_1 = drb_ffi__ZTSi_FromRuby(state, args[1]);
    double *ret_val = makeNoiseArr(w_0, h_1);
    return drb_ffi__ZTSPd_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_makePixelArr_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    int w_0 = drb_ffi__ZTSi_FromRuby(state, args[0]);
    int h_1 = drb_ffi__ZTSi_FromRuby(state, args[1]);
    Uint32 *ret_val = makePixelArr(w_0, h_1);
    return drb_ffi__ZTSPj_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_destroyArray_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    void *arr_0 = drb_ffi__ZTSPv_FromRuby(state, args[0]);
    destroyArray(arr_0);
    return mrb_nil_value();
}
static mrb_value drb_ffi_squirrel1d_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    int posx_0 = drb_ffi__ZTSi_FromRuby(state, args[0]);
    unsigned int seed_1 = drb_ffi__ZTSj_FromRuby(state, args[1]);
    unsigned int ret_val = squirrel1d(posx_0, seed_1);
    return drb_ffi__ZTSj_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_perlin2d_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    double x_0 = drb_ffi__ZTSd_FromRuby(state, args[0]);
    double y_1 = drb_ffi__ZTSd_FromRuby(state, args[1]);
    int seed_2 = drb_ffi__ZTSi_FromRuby(state, args[2]);
    double ret_val = perlin2d(x_0, y_1, seed_2);
    return drb_ffi__ZTSd_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_seamlessPerlin2d_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    double x_0 = drb_ffi__ZTSd_FromRuby(state, args[0]);
    double y_1 = drb_ffi__ZTSd_FromRuby(state, args[1]);
    int seed_2 = drb_ffi__ZTSi_FromRuby(state, args[2]);
    int freq_3 = drb_ffi__ZTSi_FromRuby(state, args[3]);
    double ret_val = seamlessPerlin2d(x_0, y_1, seed_2, freq_3);
    return drb_ffi__ZTSd_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_update_texture_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    double *arr_0 = drb_ffi__ZTSPd_FromRuby(state, args[0]);
    Uint32 *pixels_1 = drb_ffi__ZTSPj_FromRuby(state, args[1]);
    int w_2 = drb_ffi__ZTSi_FromRuby(state, args[2]);
    int h_3 = drb_ffi__ZTSi_FromRuby(state, args[3]);
    int freq_4 = drb_ffi__ZTSi_FromRuby(state, args[4]);
    double step_5 = drb_ffi__ZTSd_FromRuby(state, args[5]);
    update_texture(arr_0, pixels_1, w_2, h_3, freq_4, step_5);
    return mrb_nil_value();
}
static int drb_ffi_init_indirect_functions(void *(*lookup)(const char *));
DRB_FFI_EXPORT
void drb_register_c_extensions(void *(*lookup)(const char *), mrb_state *state, struct RClass *FFI) {
    if (drb_ffi_init_indirect_functions(lookup))
        return;
    struct RClass *module = mrb_define_module_under_f(state, FFI, "RE");
    struct RClass *object_class = state->object_class;
    mrb_define_module_function_f(state, module, "makeNoiseArr", drb_ffi_makeNoiseArr_Binding, MRB_ARGS_REQ(2));
    mrb_define_module_function_f(state, module, "makePixelArr", drb_ffi_makePixelArr_Binding, MRB_ARGS_REQ(2));
    mrb_define_module_function_f(state, module, "destroyArray", drb_ffi_destroyArray_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "squirrel1d", drb_ffi_squirrel1d_Binding, MRB_ARGS_REQ(2));
    mrb_define_module_function_f(state, module, "perlin2d", drb_ffi_perlin2d_Binding, MRB_ARGS_REQ(3));
    mrb_define_module_function_f(state, module, "seamlessPerlin2d", drb_ffi_seamlessPerlin2d_Binding, MRB_ARGS_REQ(4));
    mrb_define_module_function_f(state, module, "update_texture", drb_ffi_update_texture_Binding, MRB_ARGS_REQ(6));
    struct RClass *DoublePointerClass = mrb_define_class_under_f(state, module, "DoublePointer", object_class);
    mrb_define_class_method_f(state, DoublePointerClass, "new", drb_ffi__ZTSPd_New, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, DoublePointerClass, "value", drb_ffi__ZTSPd_GetValue, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, DoublePointerClass, "[]", drb_ffi__ZTSPd_GetAt, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, DoublePointerClass, "[]=", drb_ffi__ZTSPd_SetAt, MRB_ARGS_REQ(2));
    mrb_define_method_f(state, DoublePointerClass, "nil?", drb_ffi__ZTSPd_IsNil, MRB_ARGS_REQ(0));
    struct RClass *Unsigned_intPointerClass = mrb_define_class_under_f(state, module, "Unsigned_intPointer", object_class);
    mrb_define_class_method_f(state, Unsigned_intPointerClass, "new", drb_ffi__ZTSPj_New, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, Unsigned_intPointerClass, "value", drb_ffi__ZTSPj_GetValue, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, Unsigned_intPointerClass, "[]", drb_ffi__ZTSPj_GetAt, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, Unsigned_intPointerClass, "[]=", drb_ffi__ZTSPj_SetAt, MRB_ARGS_REQ(2));
    mrb_define_method_f(state, Unsigned_intPointerClass, "nil?", drb_ffi__ZTSPj_IsNil, MRB_ARGS_REQ(0));
    struct RClass *VoidPointerClass = mrb_define_class_under_f(state, module, "VoidPointer", object_class);
}
static int drb_ffi_init_indirect_functions(void *(*lookup)(const char *fnname)) {
  drb_symbol_lookup = lookup;
  if (!(drb_free_foreign_object_f = (void (*)(mrb_state *, void *)) lookup("drb_free_foreign_object"))) return -1;
  if (!(mrb_class_get_under_f = (struct RClass *(*)(mrb_state *, struct RClass *, const char *)) lookup("mrb_class_get_under"))) return -1;
  if (!(mrb_data_object_alloc_f = (struct RData *(*)(mrb_state *, struct RClass *, void *, const mrb_data_type *)) lookup("mrb_data_object_alloc"))) return -1;
  if (!(mrb_define_class_method_f = (void (*)(mrb_state *, struct RClass *, const char *, mrb_func_t, mrb_aspec)) lookup("mrb_define_class_method"))) return -1;
  if (!(mrb_define_class_under_f = (struct RClass *(*)(mrb_state *, struct RClass *, const char *, struct RClass *)) lookup("mrb_define_class_under"))) return -1;
  if (!(mrb_define_method_f = (void (*)(mrb_state *, struct RClass *, const char *, mrb_func_t, mrb_aspec)) lookup("mrb_define_method"))) return -1;
  if (!(mrb_define_module_function_f = (void (*)(mrb_state *, struct RClass *, const char *, mrb_func_t, mrb_aspec)) lookup("mrb_define_module_function"))) return -1;
  if (!(mrb_define_module_under_f = (struct RClass *(*)(mrb_state *, struct RClass *, const char *)) lookup("mrb_define_module_under"))) return -1;
  if (!(mrb_exc_get_f = (struct RClass *(*)(mrb_state *, const char *)) lookup("mrb_exc_get"))) return -1;
  if (!(mrb_get_args_f = (mrb_int (*)(mrb_state *, mrb_args_format, ...)) lookup("mrb_get_args"))) return -1;
  if (!(mrb_module_get_f = (struct RClass *(*)(mrb_state *, const char *)) lookup("mrb_module_get"))) return -1;
  if (!(mrb_module_get_under_f = (struct RClass *(*)(mrb_state *, struct RClass *, const char *)) lookup("mrb_module_get_under"))) return -1;
  if (!(mrb_raise_f = (void (*)(mrb_state *, struct RClass *, const char *)) lookup("mrb_raise"))) return -1;
  if (!(mrb_str_new_cstr_f = (mrb_value (*)(mrb_state *, const char *)) lookup("mrb_str_new_cstr"))) return -1;
  return 0;
}
