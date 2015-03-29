#ifndef V8_MACROS_H
#define V8_MACROS_H

// Convenience macros. v8 is pretty ugly. 
#define JS_STR(...) v8::String::New(__VA_ARGS__)
#define JS_INT(val) v8::Integer::New(val)
#define JS_FLOAT(val) v8::Number::New(val)
#define JS_BOOL(val) v8::Boolean::New(val)
#define JS_FUNCTION(name) v8::Handle<v8::Value> name(const v8::Arguments& args)
#define JS_METHOD(className, methodName) v8::Handle<v8::Value> className::methodName(const v8::Arguments& args) 

#define JS_OBJECT(type, thisContext) node::ObjectWrap::Unwrap<type>(thisContext)
#define JS_PROTOTYPE(fnTemplate, fnName) fnTemplate->PrototypeTemplate()->Set(v8::String::NewSymbol(#fnName), v8::FunctionTemplate::New(fnName)->GetFunction())

#define JS_STR_T v8::Local<v8::String>
#define JS_INT_T v8::Local<v8::Integer>
#define JS_FLOAT_T v8::Local<v8::Number>
#define JS_BOOL_T v8::Local<v8::Boolean>

#define SCOPE_IN v8::HandleScope scope
#define SCOPE_OUT(val) return scope.Close(val)

#endif