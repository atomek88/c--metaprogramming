#include "IndentStream.h"
// Created by Tomasz Michalik on 5/12/18.
using std::cout;
using std::endl;

namespace cspp51044 {
ostream &indent(ostream &ostr)
{
    IndentStreamBuf *out = dynamic_cast<IndentStreamBuf *>(ostr.rdbuf());
	if (nullptr != out) {
        out->myIndent += 4;
    }
    return ostr;
}

ostream &unindent(ostream &ostr)
{
    IndentStreamBuf *out = dynamic_cast<IndentStreamBuf *>(ostr.rdbuf());
    out->myIndent -= 4;
    return ostr;
}
}



