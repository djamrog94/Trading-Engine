#include "TradingEngine/Orderbook/Fill.h"
namespace TradingEngine::Orderbook {
	Fill::Fill(Orders::OrderCore& orderBase, FillAllocationAlgorithm fillAlocAlgo, uint16_t quantity, long fillId, bool isCompleteFill, std::string executionId)
		: orderBase_(orderBase), fillAllocationAlgorithm_(fillAlocAlgo), fillQuantity_(quantity), fillId_(fillId), isCompleteFill_(isCompleteFill), executionId_(executionId) {};
	

	std::string Fill::getFillExecutionId()
	{
		return executionId_ + "_" + std::to_string(fillId_);
	}

	
}