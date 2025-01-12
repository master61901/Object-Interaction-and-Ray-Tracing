#ifndef HITTABLE_LIST_CUSTOM_LIBRARY_H
#define HITTABLE_LIST_CUSTOM_LIBRARY_H

#include "hittable_custom_library.h"
    

class hittable_list : public hittable{
    public:
    hittable_list(){}
    hittable_list(hittable **l,int n){list=l;list_size=n;}
    hittable **list;
    int list_size;
    virtual bool hit(const ray& r , double t_min,double t_max,hit_detail& data_record)const;
};
    bool hittable_list::hit(const ray& r , double t_min,double t_max, hit_detail& data_record)const
    {
        hit_detail record;
        bool hit=0;
        double closest_object=t_max;
        for(int i=0;i<list_size;i++)
        {
            if(list[i]->hit(r,t_min,closest_object,record))
            {
                hit=1;
                closest_object=record.t;
                data_record=record;

            }
        }
        return hit;
    }
    

#endif