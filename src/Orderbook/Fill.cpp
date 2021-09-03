#include "TradingEngine/Orderbook/Fill.h"

namespace TradingEngine::Orderbook {
	Fill::Fill(Orders::OrderCore& orderBase) : orderBase_(orderBase) {};
}