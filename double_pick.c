#include <stdio.h>
#include <stdlib.h>

int nodes_distance(int bote_position, int destination){
    int distance=0;
    //code to calculate bot distance
    return distance;
}

bool visited_cm[12];
int main() {
    for(int i=0;i<12;i++){
        visited_cm[i]=TRUE;
    }
    int reqiured_materials[12]={};//store cms stored by H1,H2,H3,H4,H5.
    int cm[6]={5,8,15,18,28,29};//stores location to reach to pick reqiured CM.
    int bote_node=2;//stores bot current node position.
    int house[5]={13,10,23,20,27};//nodes are arranged according to H1,H2,H3,H4,H5.
    
    int cmArray[12]={4,6,7,9,14,16,17,19,24,26,28,30};//nodes as per the graph.
    int house_Array[6][2]={{11,21},{21,32},{22,32},{11},{12,22},{12}};
    //store which house to goto for cm[i].
    int house_total_requirement[5]=={2,2,2,2,2};
    int floor_array[5]={0,1,1,0,0};
    int which_material[10]={9,11,5,3,12,7,1,9,8,2};
    int place_cm[6];//stores number of house to be placed on for every cm[i].
    
    int global_distance=0;
    int store_cm1,store_cm2;
    for(int i=0;i<6;i++){
        for(int x=0;x<(place_cm[i]);x++){
            int temp_count=nodes_distance(bote_node,cm[i]);
            for(int j=0;j<6;j++){
                for(int y=0;y<(place_cm[j]);y++){
                    temp_count = temp_count + nodes_distance(cm[i],cm[j]);
                    int temp1=0;
                    temp1 = temp1 + nodes_distance(cm[j],house_Array[i][x]);
                    temp1 = temp1 + nodes_distance(house_Array[i][x], house_Array[j][y]);
                    int temp2=0;
                    temp2 = temp2 + nodes_distance(cm[j],house_Array[j][y]);
                    temp2 = temp2 + nodes_distance(house_Array[j][y], house_Array[i][x]);
                    if(temp1>temp2){
                        temp_count+=temp2;
                    }
                    else{
                        temp_count+=temp1;
                    }
                    if(count_nodes>temp_count){
                        count_nodes=temp_count;
                        store_cm1=cm[i];
                        store_cm2=cm[j];
                    }
                }
            }
        }
    }
	return 0;
}

void pick(int i){//i is the corresponding node values
    if(bd==3){
        if(visited_cm[i]){
            pick_right()//0 degree;
            visited_cm[i]=FALSE;
        }
        else{
            pick_left()//180 degree;
        }
    }
    else{
        if(visited_cm){
            pick_left();
            visited_cm[i]=FALSE;
        }
        else{
            pick_right();
        }
    }
}
