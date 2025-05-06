import numpy as np

def ellipse_residual(param_array , x ,y):
    """
    Input: (param_array : list , x : int , y : int)
    param array includes 5 parameter which are in ellipse equation
    x and y are coordinates
    
    Output: residual : int
    """
    h = param_array[0]
    k = param_array[1]
    alpha = param_array[2]
    beta = param_array[3]
    theta = param_array[4]


    term1 = (((x - h) * np.cos(theta) + (y - k) * np.sin(theta)) / alpha) ** 2
    term2 = ((-(x - h) * np.sin(theta) + (y - k) * np.cos(theta)) / beta) ** 2
    
    return term1 + term2 - 1

def jacobian_center_diff(params , x ,y , f = ellipse_residual , h=1e-6):
    """
    Input: (params : list , x : int , y : int , f : function)

    output: jacobian matrix
    """
    
    n_params = len(params)
    J = np.zeros((len(np.atleast_1d(x)), n_params))
    h = max(h, 1e-12) 
    
    for i in range(n_params):
        h_actual = h * (1 + abs(params[i]))
        
        params_forward = params.copy()
        params_forward[i] += h_actual
        params_backward = params.copy()
        params_backward[i] -= h_actual
        
        J[:, i] = (f(params_forward, x, y) - f(params_backward, x, y)) / (2 * h_actual)
    
    return J