#include <bits/stdc++.h>
using namespace std;
 
// Function for printing the corresponding Guidance Areas according to user's input
void store(map<int, tuple<string, string, string>> &map_priority, map<string, vector<string>> &mapObjectives, string objective, string &P_Desc, int &P_Id)
{
    string special_P_Desc;
    if (objective == "PJP")
    {
        special_P_Desc = P_Desc;
        P_Desc = "student";
    }
    for (int i = 0; i < 3; i++)
    {
        cout << "(" << P_Id << ")" << mapObjectives[objective][i] <<"   ";
 
        if (i == 0 && objective == "PJP")
            map_priority[P_Id] = {mapObjectives[objective][i], special_P_Desc, objective};
        else
            map_priority[P_Id] = {mapObjectives[objective][i], P_Desc, objective};
        P_Id++;
    }
    cout<<endl;
    fflush;
}
 
int main()
{
    // We map the desired area of guidance to the products so that we could efficiently access them later
    map<pair<string, string>, vector<string>> mp;
 
    mp[{"Internship Placement Preparation", "intern"}] =    {"Intern GO", "Intern ACE", "Intern PRO"};
    mp[{"Internship Placement Preparation", "placement"}] = {"Campus2Corporate", "Off Campus", "Placement Ready"};
    mp[{"Job Hunt", "student"}] =                           {"hieq.in", "Off Campus", "Placement Ready"};
    mp[{"Career Readiness", "student"}] =                   {"Industry Ready", "Industry Analysis", "Company Analysis"};
    mp[{"Industry & Company Fitment", "student"}] =         {"CareerUP", "GradXplore", "Field Engagement Index"};
    mp[{"Industry & Company Fitment", "YP"}] =              {"Career UP", "Field Engagement Index", "Industry Ready"};
    mp[{"Career Guidance", "student"}]=   {"Career Profiler", "GradXplore", "Field Engagement Index"};
    mp[{"Career Guidance", "YP"}]=        {"Career Profiler", "Field Engagement Index", "Industry Ready"};
    mp[{"Domain Fitment", "student"}]=    {"Fitment Analysis", "Domain Profiler", "Field Engagement Index"};
    mp[{"Domain Fitment", "YP"}]=         {"Fitment Analysis", "Domain Profiler", "Field Engagement Index"};
    mp[{"Behavioral Skills", "student"}]= {"Core Behavioral Skill Development", "Interpersonal Skills", "Social Intelligence Skills"};
    mp[{"Behavioral Skills", "YP"}]=      {"Core Behavioral Skill Development", "Interpersonal Skills", "Social Intelligence Skills"};
    mp[{"Cognitive Skills", "student"}]=  {"Core Cognitive Skill Development", "Analytical & Reasoning Skills", "Communication Skills"};
    mp[{"Cognitive Skills", "YP"}]=       {"Core Cognitive Skill Development", "Analytical & Reasoning Skills", "Communication Skills"};
    mp[{"Functional Skills", "student"}]= {"Core Domain Skill Development", "Domain Tool Learning & Training", "Domain Productivity Enhancer"};
    mp[{"Functional Skills", "YP"}] =     {"Core Domain Skill Development", "Domain Tool Learning & Training", "Domain Productivity Enhancer"};
    mp[{"Career Planning & Progression", "JH"}] =           {"hieq.in", "Campus2Corporate", "Placement Ready"};
    mp[{"Career Planning & Progression", "Upskilling"}] =   {"Career Planning", "Appraisal Booster", "People Management"};
    mp[{"Career Starter", "JH"}] =                          {"hieq.in", "Career Planning", "Campus2Corporate"};
    mp[{"Career Starter", "Upskilling"}] =                  {"Connect & Thrive", "Career Planning", "Appraisal Booster"};
    mp[{"Career Switch", "JH"}] =                           {"hieq.in", "Career Profiler", "Campus2Corporate"};
    mp[{"Career Switch", "Upskilling"}] =                   {"Career Planning", "hieq.in", "Connect & Thrive"};
 
    // Here we are mapping objects with desired area of guidance
    map<string, vector<string>> mapObjectives;
    mapObjectives["PJP"] = {"Internship Placement Preparation", "Job Hunt", "Career Readiness"};
    mapObjectives["CS"] = {"Industry & Company Fitment", "Career Guidance", "Domain Fitment"};
    mapObjectives["SD"] = {"Behavioral Skills", "Cognitive Skills", "Functional Skills"};
    mapObjectives["CP"] = {"Career Planning & Progression", "Career Starter", "Career Switch"};
 
    // These weights decide the output of our recommendation system
    vector<float> objective_weights = {1.0, 0.97, 0.938};
    vector<float> guidance_weights = {1.0, 0.967, 0.935, 0.90};
    vector<float> product_weights = {1.0, 0.94, 0.875};
    float equality_factor = 1.3;
 
    map<int, tuple<string, string, string>> map_priority;
    string select;
    int P_Id = 1;
    map<string, float> map1;
    string choose;
    cout<<endl;
 
    // STEP 1: Student or Young Professional
    cout << "Student (0) OR Young Professional (1) \n";
    int choice;
    cin >> choice;
    cout<<endl;
    string sub_guidance;
    string sub_category;
    sub_category = choice ? "YP" : "student"; // YP = Young Professionals
    if (!choice) //student
    {
        // STEP 2: Internship or Placement for Students
        cout << "Internship (0) OR Placement (1) \n";
        int ch;
        cin >> ch;
        cout<<endl;
        sub_guidance = ch ? "placement" : "intern";
 
        // STEP 3: Career Objectives
        cout << "Placement and Job Preparation (1) \nCareer Selection (2) \nSkill Development (3) \nEnter the no. of Career Objectives you want to select and then write their positions accordingly (at least 1)\n";
        int n;
        cin >> n;
 
        for (int i = 0; i < n; i++)
        {
            int a;
            cin >> a;
            if (a == 1)
            {
                map1["PJP"] = objective_weights[i];
                store(map_priority, mapObjectives, "PJP", sub_guidance, P_Id);
            }
            else if (a == 2)
            {
                map1["CS"] = objective_weights[i];
                store(map_priority, mapObjectives, "CS", sub_category, P_Id);
            }
            else
            {
                map1["SD"] = objective_weights[i];
                store(map_priority, mapObjectives, "SD", sub_category, P_Id);
            }
        }
    }
    else // Young Professionals
    {
        // STEP 2: Job Hunt or Upskilling for Young Professionals
        cout << "Job Hunt (0) OR Upskilling (1) ";
        cout << endl;
        int ch;
        cin >> ch;
        cout<<endl;
        sub_guidance = ch ? "Upskilling" : "JH";
 
        // STEP 3: Career Objectives
        cout << "Career Selection (1) \nSkill Development (2) \nCareer Progression (3) \nEnter the no. of Career Objectives you want to select and then write their positions accordingly (at least 1)\n";
        int n;
        cin >> n;
 
        for (int i = 0; i < n; i++)
        {
            int a;
            cin >> a;
            if (a == 1)
            {
                map1["CS"] = objective_weights[i];
                store(map_priority, mapObjectives, "CS", sub_category, P_Id);
            }
            else if (a == 2)
            {
                map1["SD"] = objective_weights[i];
                store(map_priority, mapObjectives, "SD", sub_category, P_Id);
            }
            else
            {
                map1["CP"] = objective_weights[i];
                store(map_priority, mapObjectives, "CP", sub_guidance, P_Id);
            }
        }
    }
    cout<<endl;
    cout << "Enter the no. of career objectives you want to choose and then list them according to their priorities (atleast 1 and atmost 4)\n";
 
    // mapping products with their priority values
    unordered_map<string, float> map_Prod;
 
    // STEP 4: Choosing the Desired Area of Guidance
    int no_Of_DAG;
    cin >> no_Of_DAG;
    for (int i = 0; i < no_Of_DAG; i++)
    {
        int priority;
        cin >> priority;
        tuple<string, string, string> p = map_priority[priority];
        float final_P = map1[get<2>(p)] * guidance_weights[i];
        float final_priority;
        for (int j = 0; j < 3; j++)
        {
            final_priority = final_P * product_weights[j];
            string product = mp[{get<0>(p), get<1>(p)}][j];
            if(map_Prod.find(product)!=map_Prod.end())
            {
                map_Prod[product] *= equality_factor;//Appeared multiple times
            }
            else
            {
                map_Prod[product] = final_priority;//Appeared first time
            }
        }
    }
        //Sorting the products w.r.t. highest priority
        vector<pair<float, string>> final_prods;
        for(auto prod: map_Prod)
        {
            final_prods.push_back({prod.second, prod.first});
        }
        sort(final_prods.begin(), final_prods.end());
 
        //Printing the products
        cout<<"The products we recommend are \n";
        int count=0;
        int s_no=0;
        for(int i=final_prods.size() - 1; i>=0; i--)
        {
            s_no++;
            cout<<s_no<<". "<<final_prods[i].second<<endl;
            count++;
            if(count == 5) break;
        }
}