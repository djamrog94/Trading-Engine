#include "TradingEngine/Orderbook/CancelOrder.h"
namespace TradingEngine::Orderbook {
	CancelOrder::CancelOrder(OrderCore& orderBase) : orderBase_(orderBase) {}
	CancelOrder::CancelOrder(ModifyOrder& modifyOrder) : orderBase_(modifyOrder.getCore()) {}
}
