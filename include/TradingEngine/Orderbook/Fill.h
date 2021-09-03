#pragma once
#include "TradingEngine/Orders/Order.h"
#include <string>

namespace TradingEngine::Orderbook {
	const enum FillAllocationAlgorithm
	{
		Unknown,
		Fifo,
		ProRata
	};
	class Fill
	{
	public:
		Fill(Orders::OrderCore& orderBase);
		Orders::OrderCore orderBase_;
		bool isCompleteFill_;
		uint16_t fillQuantity_;
		long fillId_;
		std::string executionId_;
		std::string fillExecutionId_;
		FillAllocationAlgorithm fillAllocationAlgorithm_;


	};

	const auto compareFill = [](Fill x, Fill y)
	{
		return x.executionId_ == y.executionId_;
	};

}
