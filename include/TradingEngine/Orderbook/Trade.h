#pragma once
#include <string>
namespace TradingEngine::Orderbook {
	class Trade
	{
	public:
		Trade();
		int securityId_;
		long price_;
		uint16_t quantity_;
		std::string executionId_;

	};
}

