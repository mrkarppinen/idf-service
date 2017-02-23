#include <node.h>

#include "SolitaireState.h"
#include "IDFSearch.h"

#include <algorithm>
#include <vector>
#include <string>


using std::vector;

namespace solitaire {

  bool isGoal(SolitaireState &st){
    return std::count(st.state.begin(), st.state.end(), 'x') == 1;
  }


  using v8::Function;
  using v8::FunctionCallbackInfo;
  using v8::Isolate;
  using v8::Local;
  using v8::Null;
  using v8::Object;
  using v8::String;
  using v8::Value;

  void RunCallback(const FunctionCallbackInfo<Value>& args) {

    Isolate* isolate = args.GetIsolate();
    Local<Function> cb = Local<Function>::Cast(args[1]);
    String::Utf8Value arg1(args[0]->ToString());


    SolitaireState startState(7,7, *arg1);
    vector<SolitaireState> path;
    IDFSearch<SolitaireState> idf;

    bool result = idf.start(startState, isGoal, path,32, 31);
    std::string res = "";

    if (result){

      for(vector<SolitaireState>::reverse_iterator rit = path.rbegin(); rit != path.rend(); rit++){
        res += rit->state + ":" + rit->getFrom() + ":"+ rit->getTarget() + ";";
      }

      //res = res.substr(0, res.size()-1);

    }else {
      res = "";
    }

    const unsigned argc = 1;
    Local<Value> argv[argc] = { String::NewFromUtf8(isolate, res.c_str()) };
    cb->Call(Null(isolate), argc, argv);
  }

  void Init(Local<Object> exports, Local<Object> module) {
    NODE_SET_METHOD(exports, "search", RunCallback);
  }

  NODE_MODULE(addon, Init)



}
