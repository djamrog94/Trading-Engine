/**
 *  @file   OrderCore.h
 *  @brief  Order core header
 *  @author David
 *  @date   2021-15-10
 ***********************************************/

#pragma once
#include <string>
#include <iostream>

namespace TradingEngine::Orders {
	class OrderCore
	{
	public:
		OrderCore(long orderId, std::string username, int securityId);

		long getOrderId() const;
		std::string getUsername() const;
		int getSecurityId() const;
	private:
		long orderId_;
		std::string username_;
		int securityId_;
	};

	std::ostream& operator << (std::ostream& outs, const OrderCore& oc);
}
