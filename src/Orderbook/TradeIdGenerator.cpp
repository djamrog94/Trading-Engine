#include "TradingEngine/Orderbook/TradeIdGenerator.h"

namespace TradingEngine::Orderbook
{
	TradeIdGenerator& TradeIdGenerator::Instance()
	{
		static TradeIdGenerator instance;
		return instance;
	}
	long TradeIdGenerator::generateTradeId()
	{
		boost::posix_time::ptime epoch(boost::gregorian::date(1970, 1, 1));
		boost::posix_time::ptime timeUTC = boost::posix_time::second_clock::universal_time();
		boost::posix_time::time_duration::sec_type x = (timeUTC - epoch).total_seconds();
		static std::atomic_long ID = x;
		return ++ID;

	}
	TradeIdGenerator::TradeIdGenerator() = default;
}
