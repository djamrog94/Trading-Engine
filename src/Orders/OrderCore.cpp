#include "TradingEngine/Orders/OrderCore.h"

namespace TradingEngine::Orders {
	long OrderCore::getOrderId() const
	{
		return orderId_;
	}

	std::string OrderCore::getUsername() const
	{
		return username_;
	}

	int OrderCore::getSecurityId() const
	{
		return securityId_;
	}

	OrderCore OrderCore::createOrderCore(long orderId, std::string username, int securityId)
	{
		OrderCore newCore = OrderCore(orderId, username, securityId);
		return newCore;
	}

	std::string OrderCore::toString() const
	{
		return std::string();
	}

	std::ostream& operator<<(std::ostream& outs, const OrderCore& oc)
	{
		return outs << "[OrderId=" << oc.getOrderId() << "]" << " - Username="
			<< oc.getUsername() << " Security=" << oc.getSecurityId() << std::endl;
	}

	OrderCore::OrderCore(long orderId, std::string username, int securityId)
		: orderId_(orderId), username_(username), securityId_(securityId) {}

	//OrderCore::OrderCore() = default;
}
