#include "TradingEngine/Orders/CancelOrder.h"
namespace TradingEngine::Orders {
	CancelOrder::CancelOrder(OrderCore& orderBase) : orderBase_(orderBase) {}
	CancelOrder::CancelOrder(ModifyOrder& modifyOrder) : orderBase_(modifyOrder.getCore()) {}
}
