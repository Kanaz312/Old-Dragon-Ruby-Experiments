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
struct drb_foreign_object_ZTSP10NoiseArray {
    drb_foreign_object_kind kind;
    NoiseArray *value;
    int should_free;
};
static mrb_data_type ForeignObjectType_ZTSP10NoiseArray = {"NoiseArray*", drb_free_foreign_object_indirect};
static NoiseArray *drb_ffi__ZTSP10NoiseArray_FromRuby(mrb_state *state, mrb_value self) {
    if (mrb_nil_p(self))
        return 0;
    return ((struct drb_foreign_object_ZTSP10NoiseArray *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTSP10NoiseArray_ToRuby(mrb_state *state, NoiseArray *value) {
    struct drb_foreign_object_ZTSP10NoiseArray *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSP10NoiseArray));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_pointer;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "RE");
    struct RClass *klass = mrb_class_get_under_f(state, module, "NoiseArrayPointer");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTSP10NoiseArray);
    return mrb_obj_value(rdata);
}
static int drb_ffi__ZTSi_FromRuby(mrb_state *state, mrb_value self) {
    return mrb_fixnum(self);
}
static mrb_value drb_ffi__ZTSi_ToRuby(mrb_state *state, int value) {
    return mrb_fixnum_value(value);
}
static double drb_ffi__ZTSd_FromRuby(mrb_state *state, mrb_value self) {
    return mrb_float(self);
}
static mrb_value drb_ffi__ZTSd_ToRuby(mrb_state *state, double value) {
    return mrb_float_value(state, value);
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
struct drb_foreign_object_ZTSP5Color {
    drb_foreign_object_kind kind;
    Color *value;
    int should_free;
};
static mrb_data_type ForeignObjectType_ZTSP5Color = {"Color*", drb_free_foreign_object_indirect};
static Color *drb_ffi__ZTSP5Color_FromRuby(mrb_state *state, mrb_value self) {
    if (mrb_nil_p(self))
        return 0;
    return ((struct drb_foreign_object_ZTSP5Color *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTSP5Color_ToRuby(mrb_state *state, Color *value) {
    struct drb_foreign_object_ZTSP5Color *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSP5Color));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_pointer;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "RE");
    struct RClass *klass = mrb_class_get_under_f(state, module, "ColorPointer");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTSP5Color);
    return mrb_obj_value(rdata);
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
struct drb_foreign_object_ZTSP7Texture {
    drb_foreign_object_kind kind;
    Texture *value;
    int should_free;
};
static mrb_data_type ForeignObjectType_ZTSP7Texture = {"Texture*", drb_free_foreign_object_indirect};
static Texture *drb_ffi__ZTSP7Texture_FromRuby(mrb_state *state, mrb_value self) {
    if (mrb_nil_p(self))
        return 0;
    return ((struct drb_foreign_object_ZTSP7Texture *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTSP7Texture_ToRuby(mrb_state *state, Texture *value) {
    struct drb_foreign_object_ZTSP7Texture *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSP7Texture));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_pointer;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "RE");
    struct RClass *klass = mrb_class_get_under_f(state, module, "TexturePointer");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTSP7Texture);
    return mrb_obj_value(rdata);
}
struct drb_foreign_object_ZTSPc {
    drb_foreign_object_kind kind;
    char *value;
    int should_free;
};
static mrb_data_type ForeignObjectType_ZTSPc = {"char*", drb_free_foreign_object_indirect};
static char *drb_ffi__ZTSPc_FromRuby(mrb_state *state, mrb_value self) {
    if (mrb_nil_p(self))
        return 0;
    if (mrb_type(self) == MRB_TT_STRING)
        return RSTRING_PTR(self);
    return ((struct drb_foreign_object_ZTSPc *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTSPc_ToRuby(mrb_state *state, char *value) {
    struct drb_foreign_object_ZTSPc *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSPc));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_pointer;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "RE");
    struct RClass *klass = mrb_class_get_under_f(state, module, "CharPointer");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTSPc);
    return mrb_obj_value(rdata);
}
struct drb_foreign_object_ZTSP12ShaderSprite {
    drb_foreign_object_kind kind;
    ShaderSprite *value;
    int should_free;
};
static mrb_data_type ForeignObjectType_ZTSP12ShaderSprite = {"ShaderSprite*", drb_free_foreign_object_indirect};
static ShaderSprite *drb_ffi__ZTSP12ShaderSprite_FromRuby(mrb_state *state, mrb_value self) {
    if (mrb_nil_p(self))
        return 0;
    return ((struct drb_foreign_object_ZTSP12ShaderSprite *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTSP12ShaderSprite_ToRuby(mrb_state *state, ShaderSprite *value) {
    struct drb_foreign_object_ZTSP12ShaderSprite *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSP12ShaderSprite));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_pointer;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "RE");
    struct RClass *klass = mrb_class_get_under_f(state, module, "ShaderSpritePointer");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTSP12ShaderSprite);
    return mrb_obj_value(rdata);
}
struct drb_foreign_object_ZTS10NoiseArray {
    drb_foreign_object_kind kind;
    NoiseArray value;
};
static mrb_data_type ForeignObjectType_ZTS10NoiseArray = {"NoiseArray", drb_free_foreign_object_indirect};
static NoiseArray drb_ffi__ZTS10NoiseArray_FromRuby(mrb_state *state, mrb_value self) {
    return ((struct drb_foreign_object_ZTS10NoiseArray *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTS10NoiseArray_ToRuby(mrb_state *state, NoiseArray value) {
    struct drb_foreign_object_ZTS10NoiseArray *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS10NoiseArray));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_struct;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "RE");
    struct RClass *klass = mrb_class_get_under_f(state, module, "NoiseArray");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTS10NoiseArray);
    return mrb_obj_value(rdata);
}
struct drb_foreign_object_ZTS5Color {
    drb_foreign_object_kind kind;
    Color value;
};
static mrb_data_type ForeignObjectType_ZTS5Color = {"Color", drb_free_foreign_object_indirect};
static Color drb_ffi__ZTS5Color_FromRuby(mrb_state *state, mrb_value self) {
    return ((struct drb_foreign_object_ZTS5Color *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTS5Color_ToRuby(mrb_state *state, Color value) {
    struct drb_foreign_object_ZTS5Color *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS5Color));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_struct;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "RE");
    struct RClass *klass = mrb_class_get_under_f(state, module, "Color");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTS5Color);
    return mrb_obj_value(rdata);
}
struct drb_foreign_object_ZTS7Texture {
    drb_foreign_object_kind kind;
    Texture value;
};
static mrb_data_type ForeignObjectType_ZTS7Texture = {"Texture", drb_free_foreign_object_indirect};
static Texture drb_ffi__ZTS7Texture_FromRuby(mrb_state *state, mrb_value self) {
    return ((struct drb_foreign_object_ZTS7Texture *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTS7Texture_ToRuby(mrb_state *state, Texture value) {
    struct drb_foreign_object_ZTS7Texture *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS7Texture));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_struct;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "RE");
    struct RClass *klass = mrb_class_get_under_f(state, module, "Texture");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTS7Texture);
    return mrb_obj_value(rdata);
}
static char drb_ffi__ZTSc_FromRuby(mrb_state *state, mrb_value self) {
    return mrb_fixnum(self);
}
static mrb_value drb_ffi__ZTSc_ToRuby(mrb_state *state, char value) {
    return mrb_fixnum_value(value);
}
struct drb_foreign_object_ZTS12ShaderSprite {
    drb_foreign_object_kind kind;
    ShaderSprite value;
};
static mrb_data_type ForeignObjectType_ZTS12ShaderSprite = {"ShaderSprite", drb_free_foreign_object_indirect};
static ShaderSprite drb_ffi__ZTS12ShaderSprite_FromRuby(mrb_state *state, mrb_value self) {
    return ((struct drb_foreign_object_ZTS12ShaderSprite *)DATA_PTR(self))->value;
}
static mrb_value drb_ffi__ZTS12ShaderSprite_ToRuby(mrb_state *state, ShaderSprite value) {
    struct drb_foreign_object_ZTS12ShaderSprite *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS12ShaderSprite));
    ptr->value = value;
    ptr->kind = drb_foreign_object_kind_struct;
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "RE");
    struct RClass *klass = mrb_class_get_under_f(state, module, "ShaderSprite");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTS12ShaderSprite);
    return mrb_obj_value(rdata);
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
static mrb_value drb_ffi__ZTSP10NoiseArray_New(mrb_state *mrb, mrb_value self) {
    struct drb_foreign_object_ZTSP10NoiseArray *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSP10NoiseArray));
    ptr->kind = drb_foreign_object_kind_pointer;
    ptr->value = calloc(1, sizeof(NoiseArray));
    ptr->should_free = 1;
    struct RClass *FFI = mrb_module_get_f(mrb, "FFI");
    struct RClass *module = mrb_module_get_under_f(mrb, FFI, "RE");
    struct RClass *klass = mrb_class_get_under_f(mrb, module, "NoiseArrayPointer");
    struct RData *rdata = mrb_data_object_alloc_f(mrb, klass, ptr, &ForeignObjectType_ZTSP10NoiseArray);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTSP10NoiseArray_GetValue(mrb_state *mrb, mrb_value value) {
    return drb_ffi__ZTS10NoiseArray_ToRuby(mrb, *drb_ffi__ZTSP10NoiseArray_FromRuby(mrb, value));
}
static mrb_value drb_ffi__ZTSP10NoiseArray_IsNil(mrb_state *state, mrb_value self) {
    if (drb_ffi__ZTSP10NoiseArray_FromRuby(state, self) == 0)
        return mrb_true_value();
    else
        return mrb_false_value();
}
static mrb_value drb_ffi__ZTSP10NoiseArray_GetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    return drb_ffi__ZTS10NoiseArray_ToRuby(mrb, drb_ffi__ZTSP10NoiseArray_FromRuby(mrb, self)[index]);
}
static mrb_value drb_ffi__ZTSP10NoiseArray_SetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    NoiseArray new_value = drb_ffi__ZTS10NoiseArray_FromRuby(mrb, args[1]);
    drb_ffi__ZTSP10NoiseArray_FromRuby(mrb, self)[index] = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTSP5Color_New(mrb_state *mrb, mrb_value self) {
    struct drb_foreign_object_ZTSP5Color *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSP5Color));
    ptr->kind = drb_foreign_object_kind_pointer;
    ptr->value = calloc(1, sizeof(Color));
    ptr->should_free = 1;
    struct RClass *FFI = mrb_module_get_f(mrb, "FFI");
    struct RClass *module = mrb_module_get_under_f(mrb, FFI, "RE");
    struct RClass *klass = mrb_class_get_under_f(mrb, module, "ColorPointer");
    struct RData *rdata = mrb_data_object_alloc_f(mrb, klass, ptr, &ForeignObjectType_ZTSP5Color);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTSP5Color_GetValue(mrb_state *mrb, mrb_value value) {
    return drb_ffi__ZTS5Color_ToRuby(mrb, *drb_ffi__ZTSP5Color_FromRuby(mrb, value));
}
static mrb_value drb_ffi__ZTSP5Color_IsNil(mrb_state *state, mrb_value self) {
    if (drb_ffi__ZTSP5Color_FromRuby(state, self) == 0)
        return mrb_true_value();
    else
        return mrb_false_value();
}
static mrb_value drb_ffi__ZTSP5Color_GetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    return drb_ffi__ZTS5Color_ToRuby(mrb, drb_ffi__ZTSP5Color_FromRuby(mrb, self)[index]);
}
static mrb_value drb_ffi__ZTSP5Color_SetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    Color new_value = drb_ffi__ZTS5Color_FromRuby(mrb, args[1]);
    drb_ffi__ZTSP5Color_FromRuby(mrb, self)[index] = new_value;
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
static mrb_value drb_ffi__ZTSP7Texture_New(mrb_state *mrb, mrb_value self) {
    struct drb_foreign_object_ZTSP7Texture *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSP7Texture));
    ptr->kind = drb_foreign_object_kind_pointer;
    ptr->value = calloc(1, sizeof(Texture));
    ptr->should_free = 1;
    struct RClass *FFI = mrb_module_get_f(mrb, "FFI");
    struct RClass *module = mrb_module_get_under_f(mrb, FFI, "RE");
    struct RClass *klass = mrb_class_get_under_f(mrb, module, "TexturePointer");
    struct RData *rdata = mrb_data_object_alloc_f(mrb, klass, ptr, &ForeignObjectType_ZTSP7Texture);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTSP7Texture_GetValue(mrb_state *mrb, mrb_value value) {
    return drb_ffi__ZTS7Texture_ToRuby(mrb, *drb_ffi__ZTSP7Texture_FromRuby(mrb, value));
}
static mrb_value drb_ffi__ZTSP7Texture_IsNil(mrb_state *state, mrb_value self) {
    if (drb_ffi__ZTSP7Texture_FromRuby(state, self) == 0)
        return mrb_true_value();
    else
        return mrb_false_value();
}
static mrb_value drb_ffi__ZTSP7Texture_GetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    return drb_ffi__ZTS7Texture_ToRuby(mrb, drb_ffi__ZTSP7Texture_FromRuby(mrb, self)[index]);
}
static mrb_value drb_ffi__ZTSP7Texture_SetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    Texture new_value = drb_ffi__ZTS7Texture_FromRuby(mrb, args[1]);
    drb_ffi__ZTSP7Texture_FromRuby(mrb, self)[index] = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTSPc_New(mrb_state *mrb, mrb_value self) {
    struct drb_foreign_object_ZTSPc *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSPc));
    ptr->kind = drb_foreign_object_kind_pointer;
    ptr->value = calloc(1, sizeof(char));
    ptr->should_free = 1;
    struct RClass *FFI = mrb_module_get_f(mrb, "FFI");
    struct RClass *module = mrb_module_get_under_f(mrb, FFI, "RE");
    struct RClass *klass = mrb_class_get_under_f(mrb, module, "CharPointer");
    struct RData *rdata = mrb_data_object_alloc_f(mrb, klass, ptr, &ForeignObjectType_ZTSPc);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTSPc_GetValue(mrb_state *mrb, mrb_value value) {
    return drb_ffi__ZTSc_ToRuby(mrb, *drb_ffi__ZTSPc_FromRuby(mrb, value));
}
static mrb_value drb_ffi__ZTSPc_IsNil(mrb_state *state, mrb_value self) {
    if (drb_ffi__ZTSPc_FromRuby(state, self) == 0)
        return mrb_true_value();
    else
        return mrb_false_value();
}
static mrb_value drb_ffi__ZTSPc_GetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    return drb_ffi__ZTSc_ToRuby(mrb, drb_ffi__ZTSPc_FromRuby(mrb, self)[index]);
}
static mrb_value drb_ffi__ZTSPc_SetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    char new_value = drb_ffi__ZTSc_FromRuby(mrb, args[1]);
    drb_ffi__ZTSPc_FromRuby(mrb, self)[index] = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTSPc_GetString(mrb_state *state, mrb_value self) {
    return mrb_str_new_cstr_f(state, drb_ffi__ZTSPc_FromRuby(state, self));
}
static mrb_value drb_ffi__ZTSP12ShaderSprite_New(mrb_state *mrb, mrb_value self) {
    struct drb_foreign_object_ZTSP12ShaderSprite *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTSP12ShaderSprite));
    ptr->kind = drb_foreign_object_kind_pointer;
    ptr->value = calloc(1, sizeof(ShaderSprite));
    ptr->should_free = 1;
    struct RClass *FFI = mrb_module_get_f(mrb, "FFI");
    struct RClass *module = mrb_module_get_under_f(mrb, FFI, "RE");
    struct RClass *klass = mrb_class_get_under_f(mrb, module, "ShaderSpritePointer");
    struct RData *rdata = mrb_data_object_alloc_f(mrb, klass, ptr, &ForeignObjectType_ZTSP12ShaderSprite);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTSP12ShaderSprite_GetValue(mrb_state *mrb, mrb_value value) {
    return drb_ffi__ZTS12ShaderSprite_ToRuby(mrb, *drb_ffi__ZTSP12ShaderSprite_FromRuby(mrb, value));
}
static mrb_value drb_ffi__ZTSP12ShaderSprite_IsNil(mrb_state *state, mrb_value self) {
    if (drb_ffi__ZTSP12ShaderSprite_FromRuby(state, self) == 0)
        return mrb_true_value();
    else
        return mrb_false_value();
}
static mrb_value drb_ffi__ZTSP12ShaderSprite_GetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    return drb_ffi__ZTS12ShaderSprite_ToRuby(mrb, drb_ffi__ZTSP12ShaderSprite_FromRuby(mrb, self)[index]);
}
static mrb_value drb_ffi__ZTSP12ShaderSprite_SetAt(mrb_state *mrb, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(mrb, "*", &args, &argc);
    int index = drb_ffi__ZTSi_FromRuby(mrb, args[0]);
    ShaderSprite new_value = drb_ffi__ZTS12ShaderSprite_FromRuby(mrb, args[1]);
    drb_ffi__ZTSP12ShaderSprite_FromRuby(mrb, self)[index] = new_value;
    return mrb_nil_value();
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
static mrb_value drb_ffi__ZTS10NoiseArray_New(mrb_state *state, mrb_value self) {
    struct drb_foreign_object_ZTS10NoiseArray *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS10NoiseArray *));
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "RE");
    struct RClass *klass = mrb_class_get_under_f(state, module, "NoiseArray");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTS10NoiseArray);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTS10NoiseArray_values_Get(mrb_state *state, mrb_value self) {
    NoiseArray record = drb_ffi__ZTS10NoiseArray_FromRuby(state, self);
    return drb_ffi__ZTSPd_ToRuby(state, record.values);
}
static mrb_value drb_ffi__ZTS10NoiseArray_values_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    double *new_value = drb_ffi__ZTSPd_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS10NoiseArray *)DATA_PTR(self))->value)->values = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS10NoiseArray_w_Get(mrb_state *state, mrb_value self) {
    NoiseArray record = drb_ffi__ZTS10NoiseArray_FromRuby(state, self);
    return drb_ffi__ZTSi_ToRuby(state, record.w);
}
static mrb_value drb_ffi__ZTS10NoiseArray_w_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    int new_value = drb_ffi__ZTSi_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS10NoiseArray *)DATA_PTR(self))->value)->w = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS10NoiseArray_h_Get(mrb_state *state, mrb_value self) {
    NoiseArray record = drb_ffi__ZTS10NoiseArray_FromRuby(state, self);
    return drb_ffi__ZTSi_ToRuby(state, record.h);
}
static mrb_value drb_ffi__ZTS10NoiseArray_h_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    int new_value = drb_ffi__ZTSi_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS10NoiseArray *)DATA_PTR(self))->value)->h = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS5Color_New(mrb_state *state, mrb_value self) {
    struct drb_foreign_object_ZTS5Color *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS5Color *));
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "RE");
    struct RClass *klass = mrb_class_get_under_f(state, module, "Color");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTS5Color);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTS5Color_r_Get(mrb_state *state, mrb_value self) {
    Color record = drb_ffi__ZTS5Color_FromRuby(state, self);
    return drb_ffi__ZTSd_ToRuby(state, record.r);
}
static mrb_value drb_ffi__ZTS5Color_r_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    double new_value = drb_ffi__ZTSd_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS5Color *)DATA_PTR(self))->value)->r = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS5Color_g_Get(mrb_state *state, mrb_value self) {
    Color record = drb_ffi__ZTS5Color_FromRuby(state, self);
    return drb_ffi__ZTSd_ToRuby(state, record.g);
}
static mrb_value drb_ffi__ZTS5Color_g_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    double new_value = drb_ffi__ZTSd_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS5Color *)DATA_PTR(self))->value)->g = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS5Color_b_Get(mrb_state *state, mrb_value self) {
    Color record = drb_ffi__ZTS5Color_FromRuby(state, self);
    return drb_ffi__ZTSd_ToRuby(state, record.b);
}
static mrb_value drb_ffi__ZTS5Color_b_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    double new_value = drb_ffi__ZTSd_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS5Color *)DATA_PTR(self))->value)->b = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS5Color_a_Get(mrb_state *state, mrb_value self) {
    Color record = drb_ffi__ZTS5Color_FromRuby(state, self);
    return drb_ffi__ZTSd_ToRuby(state, record.a);
}
static mrb_value drb_ffi__ZTS5Color_a_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    double new_value = drb_ffi__ZTSd_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS5Color *)DATA_PTR(self))->value)->a = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS7Texture_New(mrb_state *state, mrb_value self) {
    struct drb_foreign_object_ZTS7Texture *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS7Texture *));
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "RE");
    struct RClass *klass = mrb_class_get_under_f(state, module, "Texture");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTS7Texture);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTS7Texture_pixels_Get(mrb_state *state, mrb_value self) {
    Texture record = drb_ffi__ZTS7Texture_FromRuby(state, self);
    return drb_ffi__ZTSP5Color_ToRuby(state, record.pixels);
}
static mrb_value drb_ffi__ZTS7Texture_pixels_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Color *new_value = drb_ffi__ZTSP5Color_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS7Texture *)DATA_PTR(self))->value)->pixels = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS7Texture_w_Get(mrb_state *state, mrb_value self) {
    Texture record = drb_ffi__ZTS7Texture_FromRuby(state, self);
    return drb_ffi__ZTSi_ToRuby(state, record.w);
}
static mrb_value drb_ffi__ZTS7Texture_w_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    int new_value = drb_ffi__ZTSi_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS7Texture *)DATA_PTR(self))->value)->w = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS7Texture_h_Get(mrb_state *state, mrb_value self) {
    Texture record = drb_ffi__ZTS7Texture_FromRuby(state, self);
    return drb_ffi__ZTSi_ToRuby(state, record.h);
}
static mrb_value drb_ffi__ZTS7Texture_h_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    int new_value = drb_ffi__ZTSi_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS7Texture *)DATA_PTR(self))->value)->h = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS12ShaderSprite_New(mrb_state *state, mrb_value self) {
    struct drb_foreign_object_ZTS12ShaderSprite *ptr = calloc(1, sizeof(struct drb_foreign_object_ZTS12ShaderSprite *));
    struct RClass *FFI = mrb_module_get_f(state, "FFI");
    struct RClass *module = mrb_module_get_under_f(state, FFI, "RE");
    struct RClass *klass = mrb_class_get_under_f(state, module, "ShaderSprite");
    struct RData *rdata = mrb_data_object_alloc_f(state, klass, ptr, &ForeignObjectType_ZTS12ShaderSprite);
    return mrb_obj_value(rdata);
}
static mrb_value drb_ffi__ZTS12ShaderSprite_pixels_Get(mrb_state *state, mrb_value self) {
    ShaderSprite record = drb_ffi__ZTS12ShaderSprite_FromRuby(state, self);
    return drb_ffi__ZTSPj_ToRuby(state, record.pixels);
}
static mrb_value drb_ffi__ZTS12ShaderSprite_pixels_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 *new_value = drb_ffi__ZTSPj_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS12ShaderSprite *)DATA_PTR(self))->value)->pixels = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS12ShaderSprite_w_Get(mrb_state *state, mrb_value self) {
    ShaderSprite record = drb_ffi__ZTS12ShaderSprite_FromRuby(state, self);
    return drb_ffi__ZTSi_ToRuby(state, record.w);
}
static mrb_value drb_ffi__ZTS12ShaderSprite_w_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    int new_value = drb_ffi__ZTSi_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS12ShaderSprite *)DATA_PTR(self))->value)->w = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS12ShaderSprite_h_Get(mrb_state *state, mrb_value self) {
    ShaderSprite record = drb_ffi__ZTS12ShaderSprite_FromRuby(state, self);
    return drb_ffi__ZTSi_ToRuby(state, record.h);
}
static mrb_value drb_ffi__ZTS12ShaderSprite_h_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    int new_value = drb_ffi__ZTSi_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS12ShaderSprite *)DATA_PTR(self))->value)->h = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi__ZTS12ShaderSprite_symbol_Get(mrb_state *state, mrb_value self) {
    ShaderSprite record = drb_ffi__ZTS12ShaderSprite_FromRuby(state, self);
    return drb_ffi__ZTSPc_ToRuby(state, record.symbol);
}
static mrb_value drb_ffi__ZTS12ShaderSprite_symbol_Set(mrb_state *state, mrb_value self) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    char *new_value = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    (&((struct drb_foreign_object_ZTS12ShaderSprite *)DATA_PTR(self))->value)->symbol = new_value;
    return mrb_nil_value();
}
static mrb_value drb_ffi_makeSeamlessNoiseArr_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    int w_0 = drb_ffi__ZTSi_FromRuby(state, args[0]);
    int h_1 = drb_ffi__ZTSi_FromRuby(state, args[1]);
    int octaves_2 = drb_ffi__ZTSi_FromRuby(state, args[2]);
    double persistence_3 = drb_ffi__ZTSd_FromRuby(state, args[3]);
    int seed_4 = drb_ffi__ZTSi_FromRuby(state, args[4]);
    int end_freq_5 = drb_ffi__ZTSi_FromRuby(state, args[5]);
    NoiseArray *ret_val = makeSeamlessNoiseArr(w_0, h_1, octaves_2, persistence_3, seed_4, end_freq_5);
    return drb_ffi__ZTSP10NoiseArray_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_normalizePerlin_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    NoiseArray *noise_0 = drb_ffi__ZTSP10NoiseArray_FromRuby(state, args[0]);
    normalizePerlin(noise_0);
    return mrb_nil_value();
}
static mrb_value drb_ffi_destoryNoise_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    NoiseArray *noise_0 = drb_ffi__ZTSP10NoiseArray_FromRuby(state, args[0]);
    destoryNoise(noise_0);
    return mrb_nil_value();
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
static mrb_value drb_ffi_uintArrayToColorArray_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Uint32 *original_0 = drb_ffi__ZTSPj_FromRuby(state, args[0]);
    int w_1 = drb_ffi__ZTSi_FromRuby(state, args[1]);
    int h_2 = drb_ffi__ZTSi_FromRuby(state, args[2]);
    Color *ret_val = uintArrayToColorArray(original_0, w_1, h_2);
    return drb_ffi__ZTSP5Color_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_loadColorTexture_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    char *path_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    Texture *ret_val = loadColorTexture(path_0);
    return drb_ffi__ZTSP7Texture_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_makeShaderSprite_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    char *sprite_symbol_0 = drb_ffi__ZTSPc_FromRuby(state, args[0]);
    int sprite_w_1 = drb_ffi__ZTSi_FromRuby(state, args[1]);
    int sprite_h_2 = drb_ffi__ZTSi_FromRuby(state, args[2]);
    ShaderSprite *ret_val = makeShaderSprite(sprite_symbol_0, sprite_w_1, sprite_h_2);
    return drb_ffi__ZTSP12ShaderSprite_ToRuby(state, ret_val);
}
static mrb_value drb_ffi_changeSymbol_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    ShaderSprite *sprite_0 = drb_ffi__ZTSP12ShaderSprite_FromRuby(state, args[0]);
    char *symbol_1 = drb_ffi__ZTSPc_FromRuby(state, args[1]);
    changeSymbol(sprite_0, symbol_1);
    return mrb_nil_value();
}
static mrb_value drb_ffi_destroyTexture_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    Texture *texture_0 = drb_ffi__ZTSP7Texture_FromRuby(state, args[0]);
    destroyTexture(texture_0);
    return mrb_nil_value();
}
static mrb_value drb_ffi_destroyShaderSprite_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    ShaderSprite *sprite_0 = drb_ffi__ZTSP12ShaderSprite_FromRuby(state, args[0]);
    destroyShaderSprite(sprite_0);
    return mrb_nil_value();
}
static mrb_value drb_ffi_displayNoise_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    ShaderSprite *sprite_0 = drb_ffi__ZTSP12ShaderSprite_FromRuby(state, args[0]);
    NoiseArray *noise_1 = drb_ffi__ZTSP10NoiseArray_FromRuby(state, args[1]);
    double step_2 = drb_ffi__ZTSd_FromRuby(state, args[2]);
    displayNoise(sprite_0, noise_1, step_2);
    return mrb_nil_value();
}
static mrb_value drb_ffi_wobbleShader_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    ShaderSprite *sprite_0 = drb_ffi__ZTSP12ShaderSprite_FromRuby(state, args[0]);
    Texture *source_1 = drb_ffi__ZTSP7Texture_FromRuby(state, args[1]);
    NoiseArray *noise_2 = drb_ffi__ZTSP10NoiseArray_FromRuby(state, args[2]);
    double step_3 = drb_ffi__ZTSd_FromRuby(state, args[3]);
    double offset_strength_4 = drb_ffi__ZTSd_FromRuby(state, args[4]);
    wobbleShader(sprite_0, source_1, noise_2, step_3, offset_strength_4);
    return mrb_nil_value();
}
static mrb_value drb_ffi_horizWaveShader_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    ShaderSprite *sprite_0 = drb_ffi__ZTSP12ShaderSprite_FromRuby(state, args[0]);
    Texture *source_1 = drb_ffi__ZTSP7Texture_FromRuby(state, args[1]);
    double step_2 = drb_ffi__ZTSd_FromRuby(state, args[2]);
    double offset_strength_3 = drb_ffi__ZTSd_FromRuby(state, args[3]);
    horizWaveShader(sprite_0, source_1, step_2, offset_strength_3);
    return mrb_nil_value();
}
static mrb_value drb_ffi_wipeShader_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    ShaderSprite *sprite_0 = drb_ffi__ZTSP12ShaderSprite_FromRuby(state, args[0]);
    Texture *source_1 = drb_ffi__ZTSP7Texture_FromRuby(state, args[1]);
    Texture *wipe_texture_2 = drb_ffi__ZTSP7Texture_FromRuby(state, args[2]);
    double step_3 = drb_ffi__ZTSd_FromRuby(state, args[3]);
    wipeShader(sprite_0, source_1, wipe_texture_2, step_3);
    return mrb_nil_value();
}
static mrb_value drb_ffi_dissolveShader_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    ShaderSprite *sprite_0 = drb_ffi__ZTSP12ShaderSprite_FromRuby(state, args[0]);
    Texture *source_1 = drb_ffi__ZTSP7Texture_FromRuby(state, args[1]);
    NoiseArray *noise_2 = drb_ffi__ZTSP10NoiseArray_FromRuby(state, args[2]);
    Uint32 highlight_color_3 = drb_ffi__ZTSj_FromRuby(state, args[3]);
    double step_4 = drb_ffi__ZTSd_FromRuby(state, args[4]);
    dissolveShader(sprite_0, source_1, noise_2, highlight_color_3, step_4);
    return mrb_nil_value();
}
static mrb_value drb_ffi_dissolveFromTextureShader_Binding(mrb_state *state, mrb_value value) {
    mrb_value *args = 0;
    mrb_int argc = 0;
    mrb_get_args_f(state, "*", &args, &argc);
    ShaderSprite *sprite_0 = drb_ffi__ZTSP12ShaderSprite_FromRuby(state, args[0]);
    Texture *source_1 = drb_ffi__ZTSP7Texture_FromRuby(state, args[1]);
    Texture *dissolve_2 = drb_ffi__ZTSP7Texture_FromRuby(state, args[2]);
    Uint32 highlight_color_3 = drb_ffi__ZTSj_FromRuby(state, args[3]);
    double step_4 = drb_ffi__ZTSd_FromRuby(state, args[4]);
    dissolveFromTextureShader(sprite_0, source_1, dissolve_2, highlight_color_3, step_4);
    return mrb_nil_value();
}
static int drb_ffi_init_indirect_functions(void *(*lookup)(const char *));
DRB_FFI_EXPORT
void drb_register_c_extensions(void *(*lookup)(const char *), mrb_state *state, struct RClass *FFI) {
    if (drb_ffi_init_indirect_functions(lookup))
        return;
    struct RClass *module = mrb_define_module_under_f(state, FFI, "RE");
    struct RClass *object_class = state->object_class;
    mrb_define_module_function_f(state, module, "makeSeamlessNoiseArr", drb_ffi_makeSeamlessNoiseArr_Binding, MRB_ARGS_REQ(6));
    mrb_define_module_function_f(state, module, "normalizePerlin", drb_ffi_normalizePerlin_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "destoryNoise", drb_ffi_destoryNoise_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "destroyArray", drb_ffi_destroyArray_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "squirrel1d", drb_ffi_squirrel1d_Binding, MRB_ARGS_REQ(2));
    mrb_define_module_function_f(state, module, "perlin2d", drb_ffi_perlin2d_Binding, MRB_ARGS_REQ(3));
    mrb_define_module_function_f(state, module, "seamlessPerlin2d", drb_ffi_seamlessPerlin2d_Binding, MRB_ARGS_REQ(4));
    mrb_define_module_function_f(state, module, "uintArrayToColorArray", drb_ffi_uintArrayToColorArray_Binding, MRB_ARGS_REQ(3));
    mrb_define_module_function_f(state, module, "loadColorTexture", drb_ffi_loadColorTexture_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "makeShaderSprite", drb_ffi_makeShaderSprite_Binding, MRB_ARGS_REQ(3));
    mrb_define_module_function_f(state, module, "changeSymbol", drb_ffi_changeSymbol_Binding, MRB_ARGS_REQ(2));
    mrb_define_module_function_f(state, module, "destroyTexture", drb_ffi_destroyTexture_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "destroyShaderSprite", drb_ffi_destroyShaderSprite_Binding, MRB_ARGS_REQ(1));
    mrb_define_module_function_f(state, module, "displayNoise", drb_ffi_displayNoise_Binding, MRB_ARGS_REQ(3));
    mrb_define_module_function_f(state, module, "wobbleShader", drb_ffi_wobbleShader_Binding, MRB_ARGS_REQ(5));
    mrb_define_module_function_f(state, module, "horizWaveShader", drb_ffi_horizWaveShader_Binding, MRB_ARGS_REQ(4));
    mrb_define_module_function_f(state, module, "wipeShader", drb_ffi_wipeShader_Binding, MRB_ARGS_REQ(4));
    mrb_define_module_function_f(state, module, "dissolveShader", drb_ffi_dissolveShader_Binding, MRB_ARGS_REQ(5));
    mrb_define_module_function_f(state, module, "dissolveFromTextureShader", drb_ffi_dissolveFromTextureShader_Binding, MRB_ARGS_REQ(5));
    struct RClass *NoiseArrayPointerClass = mrb_define_class_under_f(state, module, "NoiseArrayPointer", object_class);
    mrb_define_class_method_f(state, NoiseArrayPointerClass, "new", drb_ffi__ZTSP10NoiseArray_New, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, NoiseArrayPointerClass, "value", drb_ffi__ZTSP10NoiseArray_GetValue, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, NoiseArrayPointerClass, "[]", drb_ffi__ZTSP10NoiseArray_GetAt, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, NoiseArrayPointerClass, "[]=", drb_ffi__ZTSP10NoiseArray_SetAt, MRB_ARGS_REQ(2));
    mrb_define_method_f(state, NoiseArrayPointerClass, "nil?", drb_ffi__ZTSP10NoiseArray_IsNil, MRB_ARGS_REQ(0));
    struct RClass *VoidPointerClass = mrb_define_class_under_f(state, module, "VoidPointer", object_class);
    struct RClass *ColorPointerClass = mrb_define_class_under_f(state, module, "ColorPointer", object_class);
    mrb_define_class_method_f(state, ColorPointerClass, "new", drb_ffi__ZTSP5Color_New, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ColorPointerClass, "value", drb_ffi__ZTSP5Color_GetValue, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ColorPointerClass, "[]", drb_ffi__ZTSP5Color_GetAt, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, ColorPointerClass, "[]=", drb_ffi__ZTSP5Color_SetAt, MRB_ARGS_REQ(2));
    mrb_define_method_f(state, ColorPointerClass, "nil?", drb_ffi__ZTSP5Color_IsNil, MRB_ARGS_REQ(0));
    struct RClass *Unsigned_intPointerClass = mrb_define_class_under_f(state, module, "Unsigned_intPointer", object_class);
    mrb_define_class_method_f(state, Unsigned_intPointerClass, "new", drb_ffi__ZTSPj_New, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, Unsigned_intPointerClass, "value", drb_ffi__ZTSPj_GetValue, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, Unsigned_intPointerClass, "[]", drb_ffi__ZTSPj_GetAt, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, Unsigned_intPointerClass, "[]=", drb_ffi__ZTSPj_SetAt, MRB_ARGS_REQ(2));
    mrb_define_method_f(state, Unsigned_intPointerClass, "nil?", drb_ffi__ZTSPj_IsNil, MRB_ARGS_REQ(0));
    struct RClass *TexturePointerClass = mrb_define_class_under_f(state, module, "TexturePointer", object_class);
    mrb_define_class_method_f(state, TexturePointerClass, "new", drb_ffi__ZTSP7Texture_New, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, TexturePointerClass, "value", drb_ffi__ZTSP7Texture_GetValue, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, TexturePointerClass, "[]", drb_ffi__ZTSP7Texture_GetAt, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, TexturePointerClass, "[]=", drb_ffi__ZTSP7Texture_SetAt, MRB_ARGS_REQ(2));
    mrb_define_method_f(state, TexturePointerClass, "nil?", drb_ffi__ZTSP7Texture_IsNil, MRB_ARGS_REQ(0));
    struct RClass *CharPointerClass = mrb_define_class_under_f(state, module, "CharPointer", object_class);
    mrb_define_class_method_f(state, CharPointerClass, "new", drb_ffi__ZTSPc_New, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, CharPointerClass, "value", drb_ffi__ZTSPc_GetValue, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, CharPointerClass, "[]", drb_ffi__ZTSPc_GetAt, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, CharPointerClass, "[]=", drb_ffi__ZTSPc_SetAt, MRB_ARGS_REQ(2));
    mrb_define_method_f(state, CharPointerClass, "nil?", drb_ffi__ZTSPc_IsNil, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, CharPointerClass, "str", drb_ffi__ZTSPc_GetString, MRB_ARGS_REQ(0));
    struct RClass *ShaderSpritePointerClass = mrb_define_class_under_f(state, module, "ShaderSpritePointer", object_class);
    mrb_define_class_method_f(state, ShaderSpritePointerClass, "new", drb_ffi__ZTSP12ShaderSprite_New, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ShaderSpritePointerClass, "value", drb_ffi__ZTSP12ShaderSprite_GetValue, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ShaderSpritePointerClass, "[]", drb_ffi__ZTSP12ShaderSprite_GetAt, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, ShaderSpritePointerClass, "[]=", drb_ffi__ZTSP12ShaderSprite_SetAt, MRB_ARGS_REQ(2));
    mrb_define_method_f(state, ShaderSpritePointerClass, "nil?", drb_ffi__ZTSP12ShaderSprite_IsNil, MRB_ARGS_REQ(0));
    struct RClass *DoublePointerClass = mrb_define_class_under_f(state, module, "DoublePointer", object_class);
    mrb_define_class_method_f(state, DoublePointerClass, "new", drb_ffi__ZTSPd_New, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, DoublePointerClass, "value", drb_ffi__ZTSPd_GetValue, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, DoublePointerClass, "[]", drb_ffi__ZTSPd_GetAt, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, DoublePointerClass, "[]=", drb_ffi__ZTSPd_SetAt, MRB_ARGS_REQ(2));
    mrb_define_method_f(state, DoublePointerClass, "nil?", drb_ffi__ZTSPd_IsNil, MRB_ARGS_REQ(0));
    struct RClass *NoiseArrayClass = mrb_define_class_under_f(state, module, "NoiseArray", object_class);
    mrb_define_class_method_f(state, NoiseArrayClass, "new", drb_ffi__ZTS10NoiseArray_New, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, NoiseArrayClass, "values", drb_ffi__ZTS10NoiseArray_values_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, NoiseArrayClass, "values=", drb_ffi__ZTS10NoiseArray_values_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, NoiseArrayClass, "w", drb_ffi__ZTS10NoiseArray_w_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, NoiseArrayClass, "w=", drb_ffi__ZTS10NoiseArray_w_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, NoiseArrayClass, "h", drb_ffi__ZTS10NoiseArray_h_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, NoiseArrayClass, "h=", drb_ffi__ZTS10NoiseArray_h_Set, MRB_ARGS_REQ(1));
    struct RClass *ColorClass = mrb_define_class_under_f(state, module, "Color", object_class);
    mrb_define_class_method_f(state, ColorClass, "new", drb_ffi__ZTS5Color_New, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ColorClass, "r", drb_ffi__ZTS5Color_r_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ColorClass, "r=", drb_ffi__ZTS5Color_r_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, ColorClass, "g", drb_ffi__ZTS5Color_g_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ColorClass, "g=", drb_ffi__ZTS5Color_g_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, ColorClass, "b", drb_ffi__ZTS5Color_b_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ColorClass, "b=", drb_ffi__ZTS5Color_b_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, ColorClass, "a", drb_ffi__ZTS5Color_a_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ColorClass, "a=", drb_ffi__ZTS5Color_a_Set, MRB_ARGS_REQ(1));
    struct RClass *TextureClass = mrb_define_class_under_f(state, module, "Texture", object_class);
    mrb_define_class_method_f(state, TextureClass, "new", drb_ffi__ZTS7Texture_New, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, TextureClass, "pixels", drb_ffi__ZTS7Texture_pixels_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, TextureClass, "pixels=", drb_ffi__ZTS7Texture_pixels_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, TextureClass, "w", drb_ffi__ZTS7Texture_w_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, TextureClass, "w=", drb_ffi__ZTS7Texture_w_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, TextureClass, "h", drb_ffi__ZTS7Texture_h_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, TextureClass, "h=", drb_ffi__ZTS7Texture_h_Set, MRB_ARGS_REQ(1));
    struct RClass *ShaderSpriteClass = mrb_define_class_under_f(state, module, "ShaderSprite", object_class);
    mrb_define_class_method_f(state, ShaderSpriteClass, "new", drb_ffi__ZTS12ShaderSprite_New, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ShaderSpriteClass, "pixels", drb_ffi__ZTS12ShaderSprite_pixels_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ShaderSpriteClass, "pixels=", drb_ffi__ZTS12ShaderSprite_pixels_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, ShaderSpriteClass, "w", drb_ffi__ZTS12ShaderSprite_w_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ShaderSpriteClass, "w=", drb_ffi__ZTS12ShaderSprite_w_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, ShaderSpriteClass, "h", drb_ffi__ZTS12ShaderSprite_h_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ShaderSpriteClass, "h=", drb_ffi__ZTS12ShaderSprite_h_Set, MRB_ARGS_REQ(1));
    mrb_define_method_f(state, ShaderSpriteClass, "symbol", drb_ffi__ZTS12ShaderSprite_symbol_Get, MRB_ARGS_REQ(0));
    mrb_define_method_f(state, ShaderSpriteClass, "symbol=", drb_ffi__ZTS12ShaderSprite_symbol_Set, MRB_ARGS_REQ(1));
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
