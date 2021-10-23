/**
 *  @file   Security.h
 *  @brief  Security header
 *  @author David
 *  @date   2021-15-10
 ***********************************************/

#pragma once
#include <string>
#include "TradingEngine/Orderbook/MatchingAlgorithm/MatchingAlgorithm.h"
namespace TradingEngine::Instrument {
	class Security
	{
	public:
		Security();
		Security(int securityId, std::string symbol, Orderbook::FillAllocationAlgorithm allocAlgo);
		int securityId_;
		std::string symbol_;
		Orderbook::FillAllocationAlgorithm allocAlgo_;

	};
}
