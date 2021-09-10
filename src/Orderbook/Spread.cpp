#include "TradingEngine/Orderbook/Spread.h"
namespace TradingEngine::Orderbook {
	Spread::Spread(optional<long> ask, optional<long> bid): ask_(ask), bid_(bid)
	{
	}
	optional<long> Spread::getBid()
	{
		return bid_;
	}
	optional<long> Spread::getAsk()
	{
		return ask_;
	}
}
