include <iostream>
#include <memory>
#include <string>
#include <grpc++/grpc++.h>

#include "fbp.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using fbp::Reply;
using fbp::ListReply;
using fbp::Message;
using fbp::CRMasterServer;
using namespace std;

class Client {
 public:
  Client(std::shared_ptr<Channel> channel)
      : stub_(CRMasterServer::NewStub(channel)) {}

  // Assambles the client's payload, sends it and presents the response back
  // from the server.
  std::string Login(const std::string& user) {
    // Data we are sending to the server.
    Message message;
    message.set_username(user);
    // Container for the data we expect from the server.
    Reply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->Login(&context, message, &reply);

    // Act upon its status.
    if (status.ok()) {
      return reply.msg();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }

    std::string Join(const std::string& user, std::string& room) {
    // Data we are sending to the server.
    Message message;
    message.set_username(user);
	message.set_msg(room);
    // Container for the data we expect from the server.
    Reply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->Join(&context, message, &reply);

    // Act upon its status.
    if (status.ok()) {
      return reply.msg();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }
  
    std::string Leave(const std::string& user, std::string& room) {
    // Data we are sending to the server.
    Message message;
    message.set_username(user);
	message.set_msg(room);
    // Container for the data we expect from the server.
    Reply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->Leave(&context, message, &reply);

    // Act upon its status.
    if (status.ok()) {
      return reply.msg();
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }
  
    /*ListReply List(const std::string& user) {
    // Data we are sending to the server.
    Message message;
    message.set_username(user);
    // Container for the data we expect from the server.
    ListReply reply;

    // Context for the client. It could be used to convey extra information to
    // the server and/or tweak certain RPC behaviors.
    ClientContext context;

    // The actual RPC.
    Status status = stub_->List(&context, message, &reply);

    // Act upon its status.
    if (status.ok()) {
      return reply;
    } else {
      std::cout << status.error_code() << ": " << status.error_message()
                << std::endl;
      return "RPC failed";
    }
  }*/
  
 private:
  std::unique_ptr<CRMasterServer::Stub> stub_;
};

int main(int argc, char** argv) {
  // Instantiate the client. It requires a channel, out of which the actual RPCs
  // are created. This channel models a connection to an endpoint (in this case,
  // localhost at port 50051). We indicate that the channel isn't authenticated
  // (use of InsecureChannelCredentials()).
  //ListReply lreply;
  string client_name;
  string input;
  string room_name;
  cout << "Please enter your chatroom name..." << endl;
  std::cin >> client_name;
  Client client(grpc::CreateChannel(
      "localhost:50081", grpc::InsecureChannelCredentials()));
  std::string reply = client.Login(client_name);
  std::cout << "Login State: " << reply << std::endl;
  while(input != "CHAT"){
	  cout << "Please enter a command..." << endl;
	  cin >> input;
	  cin >> room_name;
	  if(input == "LIST"){
		//lreply = client.List(client_name);
		//lreply.all_rooms
		//lreply.joined_rooms
	  }
	  else if(input == "JOIN"){
			reply = client.Join(client_name, room_name);
			std::cout << "Join: " << reply << std::endl;
		}
	  else if (input  =="LEAVE"){
		reply = client.Leave(client_name, room_name);
		std::cout << "Leave: " << reply << std::endl;
	  }
	  else if(input == "CHAT"){
		cout << "Please enter your chatroom name..." << endl;
	  }
	  else
		  cout << "Not a command..." << endl;
  }

  return 0;
}
