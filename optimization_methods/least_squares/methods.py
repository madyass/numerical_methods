import numpy as np
from function import *

def gauss_newton(initial_params, x, y, max_iteration=100, tol=1e-6):
    params = initial_params.copy()
    history = {
        'params': [initial_params.copy()],
        'residuals': [],
        'cond_numbers': []
    }
    
    for i in range(max_iteration):
        r = ellipse_residual(params, x, y)
        history['residuals'].append(np.linalg.norm(r))

        #calculating Jacobian
        J = jacobian_center_diff(params, x, y)
        
        #calculating condition numbers
        cond_num = np.linalg.cond(J)
        history['cond_numbers'].append(cond_num)
        
        #calcultaing W matrix 
        W = np.diag(1/(np.abs(r) + 1e-10))  # adding a tiny value to avoid zero matrix
        
        h_gn = np.linalg.pinv(J.T @ W @ J + 1e-8*np.eye(len(params))) @ J.T @ W @ r # taking inverse is risky , so i take psedo-inverse 
        
        new_params = params - h_gn  # updating parameters
        
        history['params'].append(new_params.copy())
        
        param_change = np.linalg.norm(new_params - params)
        grad_norm = np.linalg.norm(J.T @ W @ r)
        
        if param_change < tol*(1 + np.linalg.norm(params)):
            print(f"Converged iteration {i}")
            break
            
        if grad_norm < tol:
            print(f"Converged iteration {i}")
            break
        
        params = new_params
    
    return params, i, history


def leven_marq(initial_params, x, y, max_iteration=100, tol=1e-6, 
               lamb=1.0, lamb_inc=10, lamb_dec=0.1, rate_tol=1e-4):

    params = initial_params.copy()
    history = {'params': [], 'residuals': [], 'lambdas': [] , 'cond_numbers' : [] }
    
    for i in range(max_iteration):
        r = ellipse_residual(params, x, y)
        J = jacobian_center_diff(params, x, y)

        cond_num = np.linalg.cond(J)
        history['cond_numbers'].append(cond_num)
        
        W = np.diag(1/(np.abs(r) + 1e-10))
        
        JWJ = J.T @ W @ J
        grad = J.T @ W @ r
        diag_JWJ = np.diag(JWJ)
    
        h_lm = np.linalg.solve(JWJ + lamb*np.diag(diag_JWJ), -grad)
            
        new_params = params + h_lm
        new_r = ellipse_residual(new_params, x, y)
        
        actual_reduction = r.T @ W @ r - new_r.T @ W @ new_r
        predicted_reduction = -h_lm.T @ (grad + 0.5 * JWJ @ h_lm)
        rate = actual_reduction / (abs(predicted_reduction) + 1e-10)
        
        if rate > rate_tol:
            params = new_params
            lamb = max(lamb * lamb_dec, 1e-7)
        else:
            lamb = min(lamb * lamb_inc, 1e7)
            
        history['params'].append(params.copy())
        history['residuals'].append(np.linalg.norm(r))
        history['lambdas'].append(lamb)
        
        if np.linalg.norm(h_lm) < tol:
            break
            
    return params, i, history