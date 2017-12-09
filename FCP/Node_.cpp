#include "Node_.h"
#include "path.h"

void Node_::setPath(const string & path)
{
	m_path = NodePath(path);
}
//返回得到的消息数目
