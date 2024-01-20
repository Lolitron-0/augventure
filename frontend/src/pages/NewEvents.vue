<template>
  <div class="back">
    <div class="newEvents">
      <div class="form_for_eventNav">
        <event-navbar></event-navbar>
      </div>
      <div class="form_for_createEvent">
        <div class="title_for_createEvent">
          <p class="page_title">Create a new event</p>
        </div>

        <div class="form_title">
          <h3 class="title_text">Title</h3>
          <input type="text" class="input_form_for_title" required>
        </div>

        <div class="form_description">
          <h3 class="description_text">Description</h3>
          <textarea name="message" rows="15" cols="50"
                    class="textarea_form_for_description" required></textarea>
        </div>

        <div class="form_picture">
          <h3 class="picture_text">Picture</h3>
          <div class="form_for_picture">
            <input type="file" id="file" name="logo" class="input_form_for_picture" required>
            <label for="file" class="label_for_picture">
              <i class="ri-download-line download_vector"></i>
            </label>
          </div>
        </div>

        <div class="container_for_status">
          <h3 class="status_text">Status</h3>
          <label class="status_event">
            <input type="radio" name="status" value="now"
                   class="real_radio"
                   required>
            <span class="custom_radio"></span>
            <i class='bx bxs-stopwatch time_now_vector'></i>
            <p class="text_for_state_form">The event will start immediately after the creation is completed</p>
          </label>
          <label class="status_event">
            <input type="radio" name="status" value="later"
                   class="real_radio"
                   required>
            <span class="custom_radio"></span>
            <i class='bx bx-time-five time_later_vector'></i>
            <p class="text_for_state_form">The event will start later</p>
          </label>
        </div>

        <div class="container_btn">
          <my-button class="btn_create">Create</my-button>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
import EventNavbar from "@/components/UI/EventNavbar.vue";
import EventForm from "@/components/UI/EventForm.vue";
import MyButton from "@/components/UI/MyButton.vue";

export default {
  components: {MyButton, EventForm, EventNavbar}

}
</script>

<style scoped>
.back {
  background-color: #0d1117;
  position: fixed;
  width: 100vw;
  max-height: 100vh;
  height: 100vh;
  padding: 80px 5% 14px 5%;
  overflow-y: auto;
  overflow-x: hidden;
}
.newEvents  {
  width: 90vw;
  //border: 1px solid red;
  position: absolute;
}
.form_for_eventNav{
  width: 100%;
  height: 8%;
  //border: 1px solid green;
  border-bottom: 2px solid #24292F;
  display: flex;
  justify-content: center;
  align-items: center;
  padding-bottom: 10px;
}
.form_for_createEvent{
  //border: 1px solid yellow;
  height: 92%;
  width: 100%;
  padding: 10px;
}

.title_for_createEvent{
  width: 100%;
  //border: 1px solid #31a0a8;
  display: flex;
  justify-content: center;
  align-items: center;
}
.page_title{
  color: #587DFF;
  font-size: 18px;
  font-weight: 400;
}

.form_title, .form_description,
.form_picture, .container_for_status{
  width: 100%;
  //border: 1px solid #31a0a8;
  margin-top: 15px;
}
.title_text, .description_text,
.picture_text, .status_text{
  font-size: 16px;
  color: #587DFF;
  font-weight: 300;
}
.input_form_for_title{
  background-color: #0d1117;
  border: 1px solid #868686;
  width: 100%;
  height: 30px;
  margin-top: 10px;
  color: #cfcfcf;
  padding: 0 10px;
}

.form_for_picture{
  width: 100%;
  height: 70px;
  border: 1px solid #858585;
  justify-content: center;
  align-items: center;
  display: flex;
  margin-top: 10px;
  padding: 0;
}
.input_form_for_picture{
  width: 0;
  height: 0;
  position: absolute;
  //background-color: #858585;
  opacity: 0;
  z-index: -1;
  cursor: pointer;
}
.label_for_picture{
  width: 100%;
  height: 100%;
  //background-color: #cfcfcf;
  justify-content: center;
  align-items: center;
  display: flex;
  cursor: pointer;
}
.download_vector{
  font-size: 30px;
  color: #cfcfcf;
  cursor: pointer;
}

.textarea_form_for_description{
  background-color: #0d1117;
  border: 1px solid #868686;
  width: 100%;
  height: 100px;
  margin-top: 10px;
  color: #cfcfcf;
  resize: vertical;
  overflow: auto;
  padding: 0 10px;
}


.status_event{
  margin-top: 10px;
  width: 100%;
  //border: 1px solid green;
  display: flex;
  gap: 15px;
  align-items: center;
  padding: 2px 5px;
}
.real_radio{
  cursor: pointer;
  width: 0;
  height: 0;
  position: absolute;
  opacity: 0;
  z-index: -1;
}
.custom_radio{
  color: #cfcfcf;
  display: inline-block;
  width: 15px;
  height: 15px;
  background-color: #0d1117;
  border-radius: 50%;
  border: 2px solid #cfcfcf;
  vertical-align: text-top;
  position: relative;
}
.custom_radio::before{
  content: '';
  //display: inline-block;
  width: 10px;
  height: 10px;
  background-color: #0d1117;
  border-radius: 50%;
  border: 3.5px solid #587DFF;

  position: absolute;
  left: 50%;
  top: 50%;
  transform: translate(-50%, -50%);

  display: none;
}
.real_radio:checked + .custom_radio::before{
  display: inline-block;
}

.time_now_vector, .time_later_vector{
  color: #cfcfcf;
  font-size: 30px;
  cursor: pointer;
}
.text_for_state_form{
  color: #cfcfcf;
  font-weight: 200;
  font-size: 16px;
  padding-left: 15px;
  cursor: pointer;
}

.container_btn{
  width: 100%;
  //border: 1px solid red;
  margin-top: 10px;
  padding: 5px;
}
.btn_create{
  width: 150px;
  height: 30px;
  border: none;
  border-radius: 5px;
  font-weight: 300;
  justify-content: center;
  align-items: center;
  color: #cfcfcf;
  font-size: 16px;
}

@media (max-width: 768px) {

  .text_for_state_form{
    font-size: 15px;
  }
}
</style>