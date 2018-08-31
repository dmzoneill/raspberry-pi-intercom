#include <iostream>
#include <fstream>
#include <sstream>
#include "requesthandler.h"
#include "http.h"

// Constructor
CRequestHandler::CRequestHandler(CHttpRequest& aHttpRequest)
:mHttpRequest(aHttpRequest)
{
}

string& CRequestHandler::Response()
{
    mResponse = http::code::NOT_FOUND;
    if (mHttpRequest.mMethod == http::method::GET) {
        ifstream RequestedFile("." + mHttpRequest.mUri);
        if (RequestedFile.is_open()) {
            stringstream Response;
            Response << http::code::OK;
            Response << "Content-Type: text/html\r\n\r\n";
            Response << RequestedFile.rdbuf();
            mResponse = Response.str();
        }
    }
    return mResponse;
}
