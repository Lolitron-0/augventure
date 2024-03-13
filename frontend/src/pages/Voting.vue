<template>
  <div class="back">
    <div class="profile">
      <div class="container-for-navbar">
        <img :src="events.picture_url" alt="" class="ellipse-logo"/>
        <div class="title-event">{{ events.title }}</div>
        <i class='bx bx-dots-horizontal-rounded icon-dots' id="dots-icon" v-if="show" @click="Show" key="dots"></i>
        <div class="description-event" v-else>{{ events.description }}</div>
      </div>

      <div class="container-for-blocks-profile">
        <div class="sprint-history">
          <div class="title-for-sprint-history">Sprint history</div>
          <div class="container-for-sprints">
            <!-- здесь будет дерево спринтов
            -->
            <sprint
                v-for="(sprint, index) in sprints" :key="index"
                v-if="index <= this.countSprint"
                :state="sprint.state"
                class="sprint"
            />
          </div>
        </div>

        <div v-if="show2" class="voting-chat">
          <div class="title-for-voting-chat" v-if="events.state === 'in_progress'">Voting in progress...</div>
          <div class="title-for-voting-chat" v-else>Voting results</div>

          <div class="chat-messages" ref="messageContainer">
            <div class="message-container" >
              <div
                  v-for="(message, index) in messages"
                  :key="index"
                  :class="getMessageClasses(message)"
              >
                <div class="message-content">
                  <div class="username">{{ message.username }}</div>
                  <div class="text-with-avatar">
                    <img v-if="message.avatar !== this.user.pfp_url" :src="message.avatar" alt="" class="avatar"/>
<!--                    <div v-if="message.avatar === this.user.pfp_url" class="like">-->
<!--                      <i class='bx bxs-like icon_like'></i>-->
<!--                      {{  }}-->
<!--                    </div>-->
                    <div class="message-text">{{ message.content }}</div>
                    <div v-if="message.avatar !== this.user.pfp_url" class="like" @click="likeCounter">
                      <i class='bx bxs-like icon_like'></i>
                      <div class="count_likes"> {{ message.likes }} </div>
                    </div>
                    <div v-if="message.avatar !== this.user.pfp_url" class="end_sprint" @click="changeShow2">
                      <i class='bx bxs-party icon_end_sprint'></i>
                    </div>
                    <img v-if="message.avatar === this.user.pfp_url" :src="message.avatar" alt="" class="avatar"/>
                  </div>
                </div>
              </div>
            </div>
          </div>

          <form class="form-send-message" @submit.prevent="SendMessage">
            <input
                type="text"
                v-model="inputMessage"
                class="input-for-send-message"
                placeholder="Message"
            >
            <button type="submit" class="send-btn">
              <i class='bx bx-send icon-send' @click="SendMessage"></i>
            </button>
          </form>

        </div>
        <div v-else class="voting-chat2">
          <i class='bx bx-arrow-back icon_arrow' @click="changeShow2"></i>
          <textarea name="message" rows="15" cols="50" class="textarea_form_for_sprint" required></textarea>
          <div class="container_for_btn">
            <my-button class="btn_complete_sprint" @click="completeSprint">Continue event</my-button>
            <my-button class="btn_complete_event" @click="completeEvent">Complete the event</my-button>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<script>
import MyButton from "@/components/UI/MyButton.vue";
import { ref, push, onValue } from "firebase/database";
import { db } from "@/pages/db";
import Sprint from "@/components/UI/Sprint.vue";
export default {
  components: {Sprint, MyButton },
  data() {
    const user = JSON.parse(localStorage.getItem('user'));
    const countSprint = parseInt(localStorage.getItem('countSprint')) || 0;
    return {
      user: user,
      events: {},
      descriptionVisible: false,
      show: true,
      show2: true,
      inputMessage: "",
      likes: 0,
      messages: {},
      ID: this.$route.params.id,
      sprints: {},
      countSprint: countSprint,
    }
  },
  async beforeMount() {
    try {
      const ev = await this.$api.events.getOne(this.ID);
      this.events = ev.data.event

    } catch (error) {
      console.log('failed:', error);
    }
  },
  methods: {
    changeShow2() {
      this.show2 = !this.show2
    },
    likeCounter() {
      const messagesRef = ref(db, "message_" + this.ID);

      this.messages.likes += 1;
    },
    completeSprint() {
      // Логика для завершения спринта
      const nextSprint = this.sprints.find(sprint => sprint.state === 'voting');
      if (nextSprint) {
        nextSprint.state = 'ended';
      }
      this.countSprint += 1;
      localStorage.setItem('countSprint', this.countSprint.toString());
    },
    // async showSprint() {
    //   try {
    //     const list_sprint = await this.$api.events.listSprints();
    //     console.log("list_sprint", list_sprint)
    //     // this.sprints = ev
    //
    //   } catch (error) {
    //     console.log('failed:', error);
    //   }
    // },
    getMessageClasses(message) {
      return {
        'message-right': message.username === this.user.username,
        'message-left': message.username !== this.user.username,
      };
    },
    toggleDescription() {
      this.descriptionVisible = !this.descriptionVisible;
    },
    Show() {
      this.show = !this.show;
    },
    SendMessage() {
      const messagesRef = ref(db, "message_" + this.ID);

      if (this.inputMessage === "" || this.inputMessage === null) {
        return;
      }

      const message = {
        username: this.user.username,
        content: this.inputMessage,
        avatar: this.user.pfp_url,
        likes: this.likes
      }

      push(messagesRef, message);
      this.inputMessage = "";

    }
  },
  async mounted() {
    try {

      const messagesRef = ref(db, "message_" + this.ID);

      onValue(messagesRef, (snapshot) => {
        const data = snapshot.val();
        if (data) {
          this.messages = Object.values(data);

          this.$nextTick(() => {
            const messageContainer = this.$refs.messageContainer;
            if (messageContainer) {
              messageContainer.scrollTop = messageContainer.scrollHeight;
            }
          });
        }
      });
    } catch (error) {
      console.log("Failed to fetch messages:", error);
    }

    try {
      const list_sprint = await this.$api.sprints.listSprints();
      console.log("list_sprint", list_sprint)
      this.sprints = list_sprint.data

    } catch (error) {
      console.log('failed:', error);
    }
  },
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
  padding: 80px 5% 24px 5%;
  overflow-y: auto;
  overflow-x: hidden;
}

.profile {
  position: absolute;
  width: 85vw;
  height: 91vh;
}

.container-for-blocks-profile {
  position: relative;
  width: 100%;
  height: 83vh;
}

.sprint-history {
  position: absolute;
  left: 0;
  border: 2px solid var(--border-light-gray-color);
  border-radius: 5px;
  width: 25%;
  height: 80vh;

  display: flex;
  flex-direction: column;
  align-items: center;
}

.container-for-sprints {
  //position: absolute;
  overflow-y: auto;
  //border: 1px solid red;
  width: 100%;
  height: calc(100% - 40px);
  margin-top: 40px;
}
.container-for-sprints::-webkit-scrollbar {
  width: 0;  /* Ширина полосы прокрутки */
  height: 0; /* Высота полосы прокрутки (горизонтальная полоса) */
}

.sprint {
  position: absolute;
  margin-bottom: calc(index * 50px);
  bottom: 0;
  left: 50px;
}
.voting-chat {
  position: absolute;
  left: 28%;
  border: 2px solid var(--border-light-gray-color);
  border-radius: 5px;
  width: 72%;
  height: 80vh;
}

.container-for-navbar {
  top: 0;
  width: 100%;
  position: relative;
  height: 50px;
  display: flex;
  justify-content: left;
  align-items: center;
  gap: 30px;
  border-bottom: 1px solid var(--border-light-gray-color);
  padding: 5px 10px;
  color: #cfcfcf;
  margin-bottom: 15px;
}

.title-for-sprint-history {
  color: var(--text-wight-color);
  width: 100%;
  height: 40px;
  font-size: 18px;
  position: absolute;
  align-items: center;
  justify-content: center;
  background-color: var(--navbar-color);
  border-bottom: 1px solid var(--border-light-gray-color);
  display: flex;
  border-top-left-radius: 5px;
  border-top-right-radius: 5px;
}

.title-for-voting-chat {
  color: var(--text-wight-color);
  width: 100%;
  font-size: 18px;
  height: 40px;
  position: absolute;
  display: flex;
  align-items: center;
  justify-content: center;
  background-color: var(--navbar-color);
  border-bottom: 1px solid var(--border-light-gray-color);
  border-top-left-radius: 5px;
  border-top-right-radius: 5px;
}

.ellipse-logo {
  height: 90%;
  border: 1px solid #858585;
  box-sizing: border-box;
  background-color: #0e73bd;
  cursor: pointer;
  border-radius: 50%;
  aspect-ratio: 1;
}

.title-event {
  font-size: 18px;
}

.title-event::first-letter {
  text-transform: uppercase;
}

.description-event {
}

.icon-dots {
  font-size: 22px;
}

.form-send-message {
  position: absolute;
  width: 100%;
  height: 40px;
  border-top: 2px solid var(--border-light-gray-color);
  background-color: var(--background-app-color);
  display: flex;
  bottom: 0;
}

.input-for-send-message {
  width: calc(100% - 60px);
  font-size: 16px;
  color: var(--text-wight-color);
  height: 38px;
  background-color: var(--background-app-color);
  left: 0;
  border: none;
  padding: 0 5px 0 5px;
  justify-content: center;
  align-items: center;
  margin-right: 5px;
  border-radius: 5px;
  resize: vertical;
}

.send-btn {
  right: 10px;
  position: absolute;
  justify-content: center;
  align-items: center;
  border: none;
  background: none;
  cursor: pointer;
}

.icon-send {
  position: absolute;
  font-size: 35px;
  color: var(--text-wight-color);
  right: 10px;
  justify-content: center;
  align-items: center;
  transition: .5s;
  cursor: pointer;
}

.icon-send:hover {
  color: var(--text-turquoise-color);
}

.chat-messages {
  height: calc(100% - 80px);
  width: 100%;
  top: 40px;
  position: absolute;
  overflow-y: auto;
}

.chat-messages::-webkit-scrollbar {
  width: 0;  /* Ширина полосы прокрутки */
  height: 0; /* Высота полосы прокрутки (горизонтальная полоса) */
}

.message-container {
  padding: 10px;
  //flex: 1;
}

.avatar {
  width: 30px;
  height: 30px;
  border-radius: 50%;
  overflow: hidden;
  margin-left: 10px;
}

.message-content {
  display: flex;
  flex-direction: column;
}

.username {
  color: grey;
  margin-bottom: 5px;
}

.text-with-avatar {
  display: flex;
  align-items: flex-start;
}

.message-text {
  padding: 8px;
  border-radius: 10px;
  color: black;
  word-wrap: break-word;
  //overflow-wrap: break-word;
  word-break: break-all;
}

.message-right {
  display: flex;
  justify-content: flex-end;
  margin-bottom: 10px;
}

.message-left {
  display: flex;
  justify-content: flex-start;
  margin-bottom: 10px;
}

.message-right .avatar {
  order: 2;
  margin-left: 10px;
}

.message-left .avatar {
  order: 0;
  margin-right: 10px;
}

.message-right .message-text {
  background-color: #2ecc71;
  margin-left: 10px;
}

.message-left .message-text {
  background-color: #ffffff;
  margin-right: 10px;
}

.username.message-right {
  order: 1;
}

.username.message-left {
  order: -1;
}

.icon_like {
  color: var(--text-wight-color);
  font-size: 18px;
  cursor: pointer;
}

.icon_end_sprint {
  color: var(--text-wight-color);
  font-size: 18px;
  cursor: pointer;
}

.icon_like:hover, .icon_end_sprint:hover {
  color: var(--text-turquoise-color);
}

.like {
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
}

.count_likes {
  color: var(--text-wight-color);
}

.icon_arrow {
  color: var(--text-wight-color);
  font-size: 24px;
  margin-top: 20px;
  margin-left: 20px;
  position: absolute;
  margin-bottom: 20px;
  cursor: pointer;
  transition: .3s;
}
.icon_arrow:hover {
  color: var(--text-turquoise-color);
}
.textarea_form_for_sprint {
  background-color: var(--background-app-color);
  border: 1px solid var(--border-light-gray-color);
  //position: absolute;
  width: 80%;
  color: var(--text-wight-color);
  resize: none;
  overflow: auto;
  height: 75%;
  margin-top: 60px;
  margin-bottom: 20px;
  padding: 10px;
  outline: none;
  margin-left: 10%;
}

.textarea_form_for_sprint::-webkit-scrollbar {
  width: 0;
  height: 0;
}

.container_for_btn {
  //position: absolute;
  display: flex;
  justify-content: space-around;
  width: 100%;
  //border: 1px solid red;
  //gap: 30px;
}

.btn_complete_sprint, .btn_complete_event {
  width: 200px;
  height: 40px;
  border: none;
  border-radius: 5px;
  font-weight: 300;
  justify-content: center;
  align-items: center;
  color: var(--text-wight-color);
  font-size: 16px;
  //position: absolute;
}

.voting-chat2 {
  position: absolute;
  left: 28%;
  border: 2px solid var(--border-light-gray-color);
  border-radius: 5px;
  width: 72%;
  height: 80vh;
  display: block;
  justify-content: center;
}
</style>