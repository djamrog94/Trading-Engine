/**
 *  @file   OrderCore.cpp
 *  @brief  orer core object
 *  @author David
 *  @date   2021-15-10
 ***********************************************/

#include "TradingEngine/Orders/OrderCore.h"

namespace TradingEngine::Orders {
	/*! \brief Returns order ID for OrderCore.
	*/
	long OrderCore::getOrderId() const
	{
		return orderId_;
	}

	/*! \brief Returns username for OrderCore.
	*/
	std::string OrderCore::getUsername() const
	{
		return username_;
	}

	/*! \brief Returns security ID for OrderCore.
	*/
	int OrderCore::getSecurityId() const
	{
		return securityId_;
	}

	/*! \brief Returns reference to ostream containing string
	*		   representation of OrderCore.
	*/
	std::ostream& operator<<(std::ostream& outs, const OrderCore& oc)
	{
		return outs << "[OrderId=" << oc.getOrderId() << "]" << " - Username="
			<< oc.getUsername() << " Security=" << oc.getSecurityId() << std::endl;
	}

	/*! \brief Constructor for OrderCore.
	*/
	OrderCore::OrderCore(long orderId, std::string username, int securityId)
		: orderId_(orderId), username_(username), securityId_(securityId) {}
}
