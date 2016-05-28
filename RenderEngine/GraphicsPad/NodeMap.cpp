#include "NodeMap.h"
#include "GameLogger.h"

bool NodeMap::ReadPathingFile(std::string filename)
{
	std::ifstream inputStream(filename, std::ios::binary | std::ios::in);

	if (!inputStream.good())
	{
		GameLogger::log("ERROR : Unable to open file for reading: " + filename);
	}

	inputStream.seekg(0, std::ios::end);
	unsigned numBytes = static_cast<unsigned>(inputStream.tellg());
	inputStream.seekg(0, std::ios::beg);

	printf("Reading %u bytes\n", numBytes);
	char* texData = new (std::nothrow) char[numBytes];
	assert(texData);
	std::fill(texData, texData + numBytes - 1, 0);
	inputStream.read(texData, numBytes);
	inputStream.close();

	m_nodeData = reinterpret_cast<PathingNodes*>(texData);
	char* dataOffset = texData + sizeof(PathingNodes);
	m_nodes = reinterpret_cast<Node*>(dataOffset);
	dataOffset += sizeof(m_nodes[0]) * m_nodeData->numNodes;
	m_links = reinterpret_cast<NodeLink*>(dataOffset);

	return true;
}

void NodeMap::Dump(std::string filename)
{
	for (unsigned i = 0; i < m_nodeData->numNodes; ++i)
	{
		printf("Node[%2d] = (%7.2f, %7.2f, %7.2f), id = %2u\n", i, m_nodes[i].position.x, m_nodes[i].position.y, m_nodes[i].position.z, m_nodes[i].id);
	}
	for (unsigned i = 0; i < m_nodeData->numLinks; ++i)
	{
		printf("Link[%2d] : to = %2u, from = %2u, cost = %7.2f\n", i, m_links[i].to, m_links[i].from, m_links[i].cost);
	}
}
