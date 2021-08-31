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
		static OrderCore createOrderCore(long orderId, std::string username, int securityId);
		std::string toString() const;

	private:
		const long orderId_;
		const std::string username_;
		const int securityId_;
	};


	std::ostream& operator << (std::ostream& outs, const OrderCore& oc);
}
