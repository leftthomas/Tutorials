import heapq
def outlierCleaner(predictions, ages, net_worths):
    """
        Clean away the 10% of points that have the largest
        residual errors (difference between the prediction
        and the actual net worth).

        Return a list of tuples named cleaned_data where 
        each tuple is of the form (age, net_worth, error).
    """

    cleaned_data = []
    largest_datas = abs(predictions - net_worths)
    indexs = heapq.nlargest(int(len(predictions) * 0.1), range(len(largest_datas)), largest_datas.take)

    i = 0
    while i < len(predictions):
        if i not in indexs:
            cleaned_data.append((ages[i], net_worths[i], predictions[i]))
        i += 1
    # print(len(cleaned_data))
    return cleaned_data
