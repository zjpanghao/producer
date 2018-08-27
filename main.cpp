#include <pthread.h>
#include <map>
#include <memory>
#include <glog/logging.h>
#include "kafka_producer.h"

static void InitGlog(const char *name) {
  google::InitGoogleLogging(name);
  google::SetLogDestination(google::INFO,"log/teleloginfo");
  google::SetLogDestination(google::WARNING,"log/telelogwarn");
  google::SetLogDestination(google::GLOG_ERROR,"log/telelogerror");
  FLAGS_logbufsecs = 10;
}

int main(int argc, char*argv[]) {
  InitGlog(argv[0]);
  LOG(INFO) << "START";
  std::shared_ptr<KafkaProducer> producer1(new KafkaProducer());
  int rc = producer1->Init("192.168.1.106:9092", "t1", "group_test2");
  if (rc < 0)
    return rc;
  int index = 0;
  while (1) {
    if (index >= 32000) {
      break;
    }
    char buf[64];
    snprintf(buf, 64, "%d---messagefortest", index++);
    char topic[10];
    sprintf(topic, "zj%d", index % 10);
    producer1->Send(topic, buf, strlen(buf) + 1, 0);
    LOG(INFO) << "send " << topic;
    sleep(1);
  }
  return 0;
}

