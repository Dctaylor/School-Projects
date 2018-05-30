//
//  poly.cpp
//  David Taylor
//  COEN70L Lab 5
//
//
//

#include "poly.h"
#include <cassert>
#include <iostream>
#include <cmath>
#include <climits>


namespace coen70_lab {
    void polynomial::update_current_degree() {
        unsigned int i = MAXIMUM_DEGREE + 1;
        
        while(i >= 0) {
            if(coef[i] != 0) {
                current_degree = i;
                return;
            }
            
            --i;
        }
        
        current_degree = 0;
        return;
    }
    
    polynomial::polynomial(double c, unsigned int exponent) {
        assert(exponent <= MAXIMUM_DEGREE);
        unsigned int i;
        for(i = 0; i < MAXIMUM_DEGREE+1; ++i) {
            if(i == exponent)
                coef[i] = c;
            
            else
                coef[i] = 0;
        }
        
        if(c > 0)
            current_degree = exponent;
        
        else
            current_degree = 0;
    }
    
    void polynomial::assign_coef(double coefficient, unsigned int exponent) {
        assert(exponent <= MAXIMUM_DEGREE);
        coef[exponent] = coefficient;
        update_current_degree();
    }
    
    void polynomial::add_to_coef(double amount, unsigned int exponent) {
        assert(exponent <= MAXIMUM_DEGREE);
        coef[exponent]+=amount;
        update_current_degree();
    }
    
    void polynomial::clear() {
        unsigned int i;
        for(i = 0; i < current_degree; ++i)
            coef[i] = 0;
        
        current_degree = 0;
    }
    
    polynomial polynomial::antiderivative() const {
        assert(degree() < MAXIMUM_DEGREE);
        polynomial newPoly;
        unsigned int i;
        for(i = current_degree+1; i > 0; --i) {
            newPoly.assign_coef((coef[i-1]/(i)), i);
        }
        return newPoly;
    }
    
    double polynomial::coefficient(unsigned int exponent) const {
        if(exponent > MAXIMUM_DEGREE)
            return 0;
        
        return coef[exponent];
    }
    
    double polynomial::definite_integral(double x0, double x1) const {
        double a = 0;
        double b = 0;
        double answer;
        polynomial integral = antiderivative();
        integral.update_current_degree();
        unsigned int i;
        
        for(i = 0; i < integral.current_degree; ++i) {
            a += integral.coef[i] * (std::pow(x0,i));
            b += integral.coef[i] * (std::pow(x1,i));
        }
        answer = a - b;
        return answer;
    }

    polynomial polynomial::derivative() const {
    	polynomial newPoly;
    	unsigned int i;
    	for(i = 0; i < current_degree; ++i) {
    		newPoly.assign_coef((coef[i+1]*i+1),i);
    	}
    	return newPoly;
    }

    double polynomial::eval(double x) const {
    	double answer;
    	unsigned int i;
    	for(i = 0; i <= current_degree; ++i) {
    		answer += coef[i] * std::pow(x,i);
    	}
    }

    bool polynomial::is_zero() const {
    	if(current_degree == 0)
    		return true;

    	return false;
    }

    unsigned int polynomial::next_term(unsigned int e) const {
    	unsigned int n;
    	for(n = e+1; n <= current_degree; ++n)
    		if(coef[n] > 0)
    			return n;


    	return 0;
    }

    unsigned int polynomial::previous_term(unsigned int e) const {
    	unsigned int n;
    	for(n = e-1; n >= 0; --n)
    		if(coef[n] > 0)
    			return n;

    	return UINT_MAX;
    }

    polynomial operator +(const polynomial& p1, const polynomial& p2) {
    	polynomial newPoly;
    	unsigned int i;
    	unsigned int newDegree;
    	if(p1.degree() > p2.degree())
    		newDegree = p1.degree();
    	else
    		newDegree = p2.degree();

    	for(i = 0; i < newDegree; ++i)
    		newPoly.coef[i] = p1.coef[i] + p2.coef[i];

    	newPoly.update_current_degree();
    	return newPoly;
    }

    polynomial operator -(const polynomial& p1, const polynomial& p2) {
    	polynomial newPoly;
    	unsigned int i;
    	unsigned int newDegree;
    	if(p1.degree() > p2.degree())
    		newDegree = p1.degree();
    	else
    		newDegree = p2.degree();

    	for(i = 0; i < newDegree; ++i) {
    		if(p1.coef[i] > p2.coef[i])
    			newPoly.coef[i] = p1.coef[i] - p2.coef[i];

    		else
    			newPoly.coef[i] = p2.coef[i] - p1.coef[i];
    	}
    	newPoly.update_current_degree();
    	return newPoly;
    }

    polynomial operator *(const polynomial& p1, const polynomial& p2) {
    	assert(p1.degree( ) + p2.degree( ) <= MAXIMUM_DEGREE);
    }
}
