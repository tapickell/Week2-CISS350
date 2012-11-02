
#include <stdexcept>

using namespace std;

class ClientNotFoundError : public runtime_error
{
public:
	ClientNotFoundError() : runtime_error("Client not found"){}
};