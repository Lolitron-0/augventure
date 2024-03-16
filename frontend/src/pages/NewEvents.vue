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
          <input type="text" class="input_form_for_title" required v-model.trim="event.title">
        </div>

        <div class="form_description">
          <h3 class="description_text">Description</h3>
          <textarea name="message" rows="15" cols="50" class="textarea_form_for_description" required
            v-model.trim="event.description"></textarea>
        </div>

        <div class="form_description">
          <h3 class="description_text">Initial content</h3>
          <textarea name="message" rows="15" cols="50" class="textarea_form_for_description" required
            v-model.trim="initial_post.text_content"></textarea>
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
            <input type="radio" name="status" value="now" class="real_radio" required
              v-model.trim="creation_data.start">
            <span class="custom_radio"></span>
            <i class='bx bxs-stopwatch time_now_vector'></i>
            <p class="text_for_state_form">The event will start immediately after the creation is completed</p>
          </label>
          <label class="status_event">
            <input type="radio" name="status" value="later" class="real_radio" required
              v-model.trim="creation_data.start">
            <span class="custom_radio"></span>
            <i class='bx bx-time-five time_later_vector'></i>
            <p class="text_for_state_form">The event will start later</p>
          </label>
        </div>

        <div class="container_btn">
          <my-button class="btn_create" @click="createEvent">Create</my-button>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
import EventNavbar from "@/components/UI/EventNavbar.vue";
import EventForm from "@/components/UI/EventForm.vue";
import MyButton from "@/components/UI/MyButton.vue";
import axios from 'axios'

function formatDate(date) {
  const hrs0 = '0' + date.getUTCHours()
  const mins0 = '0' + date.getUTCMinutes()
  const secs0 = '0' + date.getUTCSeconds()
  const hrs = hrs0.substring(hrs0.length - 2)
  const mins = mins0.substring(mins0.length - 2)
  const secs = secs0.substring(secs0.length - 2)
  return `${date.getUTCFullYear()}-${date.getUTCMonth() + 1}-${date.getUTCDate()} ${hrs}:${mins}:${secs}`
}

export default {
  components: { MyButton, EventForm, EventNavbar },

  data() {
    return {
      event:
      {
        title: '',
        description: '',
        start: formatDate(new Date(new Date().getTime() - 1000)),
      },
      initial_post:
      {
        text_content: ''
      },
      creation_data:
      {
        start: "now"
      }
    }
  },
  methods: {
    async createEvent() {
      if (this.creation_data.start === "now")
        this.event.start = formatDate(new Date(new Date().getTime() - 1000));
      else
        this.event.start = formatDate(new Date(new Date().getTime() + 10000));
        
      console.log(this.event.start);

      try {
        const response = await this.$api.events.createEvent({
          event: this.event,
          initial_post: this.initial_post
        })
        console.log('Событие успешно создано:', response.data)
        this.$router.push({ name: 'profile' })
      } catch (error) {
        console.error('Ошибка при создании события:', error)
      }
    }
  }

}
</script>

<style scoped>
@import "@/styles.css";

.back {
  background-color: var(--background-app-color);
  position: fixed;
  width: 100vw;
  max-height: 100vh;
  height: 100vh;
  padding: 80px 5% 14px 5%;
  overflow-y: auto;
  overflow-x: hidden;
}

.newEvents {
  width: 90vw;
  /* border: 1px solid red; */
  position: absolute;
}

.form_for_eventNav {
  width: 100%;
  height: 8%;
  /* border: 1px solid green; */
  border-bottom: 2px solid #24292F;
  display: flex;
  justify-content: center;
  align-items: center;
  padding-bottom: 10px;
}

.form_for_createEvent {
  /* border: 1px solid yellow; */
  height: 92%;
  width: 100%;
  padding: 10px;
}

.title_for_createEvent {
  width: 100%;
  /* border: 1px solid #31a0a8; */
  display: flex;
  justify-content: center;
  align-items: center;
}

.page_title {
  color: var(--title-color);
  font-size: 18px;
  font-weight: 400;
}

.form_title,
.form_description,
.form_picture,
.container_for_status {
  width: 100%;
  /* border: 1px solid #31a0a8; */
  margin-top: 15px;
}

.title_text,
.description_text,
.picture_text,
.status_text {
  font-size: 16px;
  color: var(--title-color);
  font-weight: 300;
}

.input_form_for_title {
  background-color: var(--background-app-color);
  border: 1px solid var(--border-light-gray-color);
  width: 100%;
  height: 30px;
  margin-top: 10px;
  color: var(--text-wight-color);
  padding: 0 10px;
}

.form_for_picture {
  width: 100%;
  height: 70px;
  border: 1px solid var(--border-light-gray-color);
  justify-content: center;
  align-items: center;
  display: flex;
  margin-top: 10px;
  padding: 0;
}

.input_form_for_picture {
  width: 0;
  height: 0;
  position: absolute;
  /* background-color: #858585; */
  opacity: 0;
  z-index: -1;
  cursor: pointer;
}

.label_for_picture {
  width: 100%;
  height: 100%;
  /* background-color: #cfcfcf; */
  justify-content: center;
  align-items: center;
  display: flex;
  cursor: pointer;
}

.download_vector {
  font-size: 30px;
  color: var(--text-wight-color);
  cursor: pointer;
}

.textarea_form_for_description {
  background-color: var(--background-app-color);
  border: 1px solid var(--border-light-gray-color);
  width: 100%;
  height: 100px;
  margin-top: 10px;
  color: var(--text-wight-color);
  resize: vertical;
  overflow: auto;
  padding: 0 10px;
  outline: none;
}


.status_event {
  margin-top: 10px;
  width: 100%;
  /* border: 1px solid green; */
  display: flex;
  gap: 15px;
  align-items: center;
  padding: 2px 5px;
}

.real_radio {
  cursor: pointer;
  width: 0;
  height: 0;
  position: absolute;
  opacity: 0;
  z-index: -1;
}

.custom_radio {
  color: var(--text-wight-color);
  display: inline-block;
  width: 15px;
  height: 15px;
  background-color: var(--background-app-color);
  border-radius: 50%;
  border: 2px solid var(--text-wight-color);
  vertical-align: text-top;
  position: relative;
}

.custom_radio::before {
  content: '';
  /* display: inline-block; */
  width: 10px;
  height: 10px;
  background-color: var(--background-app-color);
  border-radius: 50%;
  border: 3.5px solid var(--text-turquoise-color);

  position: absolute;
  left: 50%;
  top: 50%;
  transform: translate(-50%, -50%);

  display: none;
}

.real_radio:checked+.custom_radio::before {
  display: inline-block;
}

.time_now_vector,
.time_later_vector {
  color: var(--text-wight-color);
  font-size: 30px;
  cursor: pointer;
}

.text_for_state_form {
  color: var(--text-wight-color);
  font-weight: 200;
  font-size: 16px;
  padding-left: 15px;
  cursor: pointer;
}

.container_btn {
  width: 100%;
  /* border: 1px solid red; */
  margin-top: 10px;
  padding: 5px;
}

.btn_create {
  width: 150px;
  height: 30px;
  border: none;
  border-radius: 5px;
  font-weight: 300;
  justify-content: center;
  align-items: center;
  color: var(--text-wight-color);
  font-size: 16px;
}

@media (max-width: 768px) {

  .text_for_state_form {
    font-size: 15px;
  }
}
</style>
