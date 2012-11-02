
#include <stdexcept>

using namespace std;

class PatError : public runtime_error
{
public:
	PatError() : runtime_error("Client is of undetermined sex"){}
};