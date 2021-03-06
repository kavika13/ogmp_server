#ifndef HTTP_REQUEST_HANDLER_HPP
#define HTTP_REQUEST_HANDLER_HPP

#include "client.hpp"
#include "client_manager.hpp"
#include "config.hpp"
#include "shared.hpp"
#include <time.h>

namespace http {
namespace server {

using namespace std;

struct reply;
struct request;

// The common handler for all incoming requests.
class request_handler {
	public:
		request_handler(const request_handler&)= delete;
		request_handler& operator=(const request_handler&)= delete;

		// Construct with a directory containing files to be served.
		explicit request_handler(config_ptr conf, const string& doc_root);

		// Handle a request and produce a reply.
		void handle_request(const request& req, reply& rep);

		// Turns a string map into an encoded string.
		string encode_output(string_map output);
		string encode_output(string_map_vector output);

	private:
		config_ptr config_;
		string doc_root_;
		client_manager client_manager_;
		time_t start_ = time(0);

		string_vector seperate_string(string input, string seperator);
		string create_new_uid(size_t length);
		bool url_decode(const string& in, string& out);
		bool handle_command(string_map& input, reply& rep);
		void prepare_reply(reply& rep, string extension = "");

};

} // namespace server
} // namespace http

#endif // HTTP_REQUEST_HANDLER_HPP
