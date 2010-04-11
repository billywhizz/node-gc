#include <node.h>
#include <node_events.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

using namespace v8;
using namespace node;

class GC : public EventEmitter {
 public:
  static void
  Initialize (v8::Handle<v8::Object> target)
  {
    HandleScope scope;

    Local<FunctionTemplate> t = FunctionTemplate::New(New);

    t->Inherit(EventEmitter::constructor_template);
    t->InstanceTemplate()->SetInternalFieldCount(1);

    NODE_SET_PROTOTYPE_METHOD(t, "collect", Collect);

    target->Set(String::NewSymbol("GC"), t->GetFunction());
  }

  void Collect() {
    while(!V8::IdleNotification()){};
  }

 protected:

  static Handle<Value>
  New (const Arguments& args)
  {
    HandleScope scope;

    GC *gc = new GC();
    gc->Wrap(args.This());

    return args.This();
  }

  static Handle<Value>
  Collect (const Arguments& args)
  {
    GC *gc = ObjectWrap::Unwrap<GC>(args.This());

    HandleScope scope;

    gc->Collect();

    return v8::Null();
  }

  GC () : EventEmitter () 
  {
  }

  ~GC ()
  {
  }
};

extern "C" void
init (Handle<Object> target) 
{
  HandleScope scope;
  GC::Initialize(target);
}
