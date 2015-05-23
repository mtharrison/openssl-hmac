#include <nan.h>
#include <openssl/hmac.h>

using namespace v8;

NAN_METHOD(hmac) {
  NanScope();

  v8::String::AsciiValue string(args[0]);
  char *key = (char *) malloc(string.length() + 1);
  strcpy(key, *string);

  v8::String::AsciiValue string2(args[1]);
  char *data = (char *) malloc(string2.length() + 1);
  strcpy(data, *string2);

  unsigned char* digest;
    
  digest = HMAC(EVP_sha1(), key, strlen(key), (unsigned char*)data, strlen(data), NULL, NULL);    

  char mdString[40];
  for(int i = 0; i < 20; i++) {
    sprintf(&mdString[i*2], "%02x", (unsigned int)digest[i]);
  }

  free(key);
  free(data);

  NanReturnValue(NanNewBufferHandle((char*)digest, 20));
}

void InitAll(Handle<Object> exports, Handle<Object> module) {
  module->Set(NanNew<String>("exports"),
    NanNew<FunctionTemplate>(hmac)->GetFunction());
}

NODE_MODULE(hmac, InitAll)
