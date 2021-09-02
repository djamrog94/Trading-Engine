#include "TradingEngine/Orders/CancelOrder.h"
namespace TradingEngine::Orders {
	CancelOrder::CancelOrder(OrderCore& orderBase) : OrderCore(orderBase.getOrderId(), orderBase.getUsername(), orderBase.getSecurityId()) {}
	CancelOrder::CancelOrder(ModifyOrder& modifyOrder) : OrderCore(modifyOrder.getOrderId(), modifyOrder.getUsername(), modifyOrder.getSecurityId()) {}
}
