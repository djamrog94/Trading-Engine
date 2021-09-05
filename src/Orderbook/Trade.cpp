#include "TradingEngine/Orderbook/Trade.h"

namespace TradingEngine::Orderbook {
	Trade::Trade(Orders::Order& order, uint16_t fillQuantity)
		: securityId_(order.getSecurityId()), price_(order.price_), quantity_(fillQuantity), currentTradeNumber_(getID())
	{
		boost::posix_time::ptime timeUTC = boost::posix_time::second_clock::universal_time();
		executionId_ = "tradeTime: " + to_iso_string(timeUTC) + ":M:" + std::to_string(currentTradeNumber_);
	}
	int Trade::getID()
	{
		static std::atomic_int ID = 0;
		return ++ID;
	}
	int Trade::getTradeNumber()
	{
		return currentTradeNumber_;
	}
	;
	
}