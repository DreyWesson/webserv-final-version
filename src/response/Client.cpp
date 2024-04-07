#include "../../inc/AllHeaders.hpp"

// Client::Client(int fd, std::string &addr, Listen &host_port, int worker_id, bool disconnect) : fd_(fd), addr_(addr), host_port_(host_port), worker_id_(worker_id), disconnect_(disconnect) {
//   request_ = NULL;
//   config_ = NULL;
//   response_ = NULL;
// }
Client::Client(Listen& host_port) : host_port_(host_port), config_(NULL) {
}


Client::~Client() {
  delete config_;
}

void Client::setupConfig(DB &db, HttpRequestParser &req_, size_t targetServerIdx) {
  (void) targetServerIdx;

  request_ = &req_;
  // std::cout << "****** STATUS: " << request_->getBody() <<std::endl;
  // printAllDBData(db.serversDB);
  // printData(getDataByIdx(db.serversDB, requestedServerIdx));


  /// @note AGGREGATED ALL CONFIGURATIONS HERE
  config_ = new RequestConfig(*request_, host_port_, db, *this);
  config_->setUp(targetServerIdx);
}

void Client::setupResponse() {
  response_ = new Response(*config_);
}