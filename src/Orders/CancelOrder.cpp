#include "TradingEngine/Orders/CancelOrder.h"
namespace TradingEngine::Orders {
	CancelOrder::CancelOrder(OrderCore& orderBase) : OrderCore(orderBase.getOrderId(), orderBase.getUsername(), orderBase.getSecurityId()), orderBase_(orderBase) {}

	std::ostream& operator<<(std::ostream& outs, const CancelOrder& co)
	{
		return outs << co.orderBase_ << std::endl;
	}
	
}
