#pragma once
#include "TradingEngine/Orders/Order.h"
#include <string>
#include <time.h>
#include <boost/date_time.hpp>
#include "TradingEngine/Orderbook/TradeIdGenerator.h"
namespace TradingEngine::Orderbook {
	class Trade
	{
	public:
		Trade(Orders::Order& order, uint16_t fillQuantity);
		int securityId_;
		long price_;
		uint16_t quantity_;
		std::string executionId_;
		int getTradeNumber();
	private:
		const int currentTradeNumber_;

	};
}

