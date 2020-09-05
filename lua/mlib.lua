print("\n-> Lua lib loaded")

function bhaskara(a, b, c)
    delta = (b * b) - (4 * a * c)
    x1 = (-b + math.sqrt(delta)) / (2 * a)
    x2 = (-b - math.sqrt(delta)) / (2 * a)
    return x1, x2
end
