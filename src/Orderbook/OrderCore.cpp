#include "TradingEngine/Orderbook/OrderCore.h"

namespace TradingEngine::Orderbook {
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
		return securityID_;
	}

	OrderCore OrderCore::createOrderCore(long orderId, std::string username, int securityId)
	{
		OrderCore newCore = OrderCore(orderId, username, securityId);
		return newCore;
	}

	std::string OrderCore::toString()
	{
		return std::string();
	}

	std::ostream& operator<<(std::ostream& outs, const OrderCore& oc)
	{
		return outs << "[OrderId=" << oc.getOrderId() << "]" << " - Username="
			<< oc.getUsername() << " Security=" << oc.getSecurityId() << std::endl;
	}

	OrderCore::OrderCore(long orderId, std::string username, int securityID)
		: orderId_(orderId), username_(username), securityID_(securityID) {}

	OrderCore::OrderCore() = default;
}
