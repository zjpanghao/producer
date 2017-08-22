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
  std::shared_ptr<KafkaProducer> producer1(new KafkaProducer());
  int rc = producer1->Init("192.168.1.85:9092,192.168.1.82:9092", "east_market", "group_test2");
  if (rc < 0)
    return rc;
  int index = 0;
  while (1) {
    char buf[64];
    snprintf(buf, 64, "%d---messagefortest", index++);
    producer1->Send(buf, strlen(buf) + 1);
    sleep(1);
  }
  return 0;
}

