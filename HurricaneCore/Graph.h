//*******************************//
//
// Name:			Graph.h
// Description:		
//
// Author:			Edwin Chen
// Special Thanks:	JP Amore
//
// Created:			Oct 21, 2017
// Last updated:	Nov 02, 2017
//
//*******************************//

#ifndef _GRAPH_H
#define _GRAPH_H

#include "Macro.h"

namespace HurricaneEngine 
{
	template <typename T>
	class Graph {
	protected:
		class GraphNode {
		protected:
			VECTOR(GraphNode*) senders;
			VECTOR(GraphNode*) receivers;
			T* _data;

		public:
			GraphNode(T* _dt) 
			{
				_data = nullptr;
				_data = _dt;
			}

			~GraphNode() 
			{
				RemoveAllConnections();
			}

			T* Data() const 
			{
				return _data;
			}

			// Connect to specific node
			void ConnectTo(GraphNode* _dt)
			{
				if (CheckExistingSender(_dt) == true)
					return;
			
				senders.Add(_dt);
			}
			
			// Make sure don't add an existing sender node
			bool CheckExistingSender(GraphNode* _gn)
			{
				for (GraphNode* temp : senders)
				{
					if (temp.Equals(_gn))
						return true;
				}
				return false;
			}
			
			void StopConnectionTo(GraphNode* _dt)
			{
				if (CheckExistingSender(_dt) == false)
					return;
			
				senders.Remove(_dt);
			}
			
			// Receive a connection for another node
			void ReceiveFrom(GraphNode* _sc)
			{
				if (CheckExistingReceiver(_sc) == true)
					return;
			
				receivers.Add(_sc);
			}
			
			// Make sure we're not already receiving from another node
			bool CheckExistingReceiver(GraphNode* _gn)
			{
				for (GraphNode* temp : receivers)
				{
					if (temp.Equals(_gn))
						return true;
				}
				return false;
			}
			
			void StopReceivingFrom(GraphNode* _sc)
			{
				if (CheckExistingReceiver(_sc) == false)
					return;
			
				receivers.Remove(_sc);
			}
			
			void RemoveAllConnections()
			{
				senders.Clear();
				receivers.Clear();
			}		
		}; // end class GraphNode
		
	protected:
		VECTOR(GraphNode*) _nodes;

	public:
		
		Graph() {}
		~Graph() 
		{
			RemoveAllNodes();
		}

		void RemoveAllNodes() 
		{
			if (IsEmpty())
				return;

			for (GraphNode* n : _nodes) 
			{
				SAFE_DELETE(n);
			}
		}


		// Find an existing node in the graph
		GraphNode* FindNode(T* _data)
		{
			GraphNode* node = nullptr;
		
			if (IsEmpty())
				return node;
		
			for (GraphNode* n : _nodes)
			{
				if (n->Data() == _data) 
				{
					node = n;
					break;
				}
			}
			return node;
		}

		inline int Count() const {
			return _nodes.size();
		}

		inline bool IsEmpty() const {
			return _nodes.empty();
		}
		
	#pragma region ADD NODE / DIRECTION funcitons
		// Add node to graph
		void AddNode(T* _data)
		{
			GraphNode* node = new GraphNode(_data);
			_nodes.Add(node);
		}
		
		// Add a one way connection b/n two nodes 
		void AddDirectedEdge(GraphNode* _srcNode, GraphNode* _dstNode)
		{
			// Make sure we're not connecting the same node to itself
			if (_srcNode == nullptr || _dstNode == nullptr || (_srcNode->Data() == _dstNode->Data())
				return;
		
			_srcNode->ConnectTo(_dstNode);
			_dstNode->ReceiveFrom(_srcNode);
		}
		
		// A public AddDirectedEdge in a easier fashion with data instead of nodes
		void AddDirectedEdge(T* _src, T* _dst)
		{
			GraphNode* srcNode = FindNode(_src);
			GraphNode* dstNode = FindNode(_dst);
		
			AddDirectedEdge(srcNode, dstNode);
		}
		
		// Quick way of adding a two way bidirectional connection b/n two nodes
		void AddBidirectionalEdge(T* _nodeA, T* _nodeB)
		{
			GraphNode* aNode = FindNode(_nodeA);
			GraphNode* bNode = FindNode(_nodeB);
		
			AddDirectedEdge(aNode, bNode);
			AddDirectedEdge(bNode, aNode);
		}

	#pragma endregion
		


	#pragma region REMOVE NODE / DIRECTION functions
		
		void RemoveNode(T* _data)
		{
			GraphNode* node = FindNode(_data);
		
			// Remove the connections of the deleted one to the remaining nodes
			for (GraphNode* nd : _nodes)
			{
				nd->StopConnectionTo(node);
				nd->StopReceivingFrom(node);
			}

			SAFE_DELETE(node);
			_nodes.shrink_to_fit();
		}
		
		void RemoveDirection(T* sc, T* dc)
		{
			GraphNode* _src = FindNode(sc);
			GraphNode* _dst = FindNode(dc);
		
			_src->StopConnectionTo(_dst);
			_dst->StopReceivingFrom(_src);
		}
		
		public void RemoveBidirection(T* _nodeA, T* _nodeB)
		{
			GraphNode* aNode = FindNode(_nodeA);
			GraphNode* bNode = FindNode(_nodeB);
		
			aNode->StopConnectionTo(bNode);
			aNode->StopReceivingFrom(bNode);
		
			bNode->StopConnectionTo(aNode);
			bNode->StopReceivingFrom(aNode);
		}
		
	#pragma endregion

	}; // end class Graph



} // end namespace HurricaneEngine

#endif