function NH1 = posteriorTrain(data, label, )
%% Calculate the distribution in each sector
    NH1 = 0;
    PH1 = length(find(label == 1)) / length(label);
    for i = 1 : length(data)
        PdH1 = 0;
        Pd = 0;
        for j = 1 : length(data)
            if (data(j) <= data(i))
                Pd = Pd + 1;
                if (label(j) == 1)
                    PdH1 = PdH1 + 1;
                end
            end
        end
        NH1 = NH1 + PdH1 / Pd * PH1;
    end
end
