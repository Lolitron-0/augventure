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

            <sprint
                v-for="(sprint, index) in this.sprints" :key="index"
                :state="index === 0 ? 'voting' : 'ended'"
                :data="sprint.start"
            />
          </div>
        </div>

        <div v-if="show2" class="voting-chat">
          <div class="title-for-voting-chat" v-if="events.state === 'in_progress'">Voting in progress...</div>
          <div class="title-for-voting-chat" v-else>Voting results</div>

          <div class="chat-messages" ref="messageContainer">
            <div class="message-container" >
              <div
                  v-for="(message, index) in eventMessages[this.ID]"
                  :key="message.id"
                  :class="getMessageClasses(message, this.user)"
              >
                <div class="message-content">
                  <div class="username">{{ message.username }}</div>
                  <div class="text-with-avatar">
                    <img v-if="message.author_id !== this.user.id" :src="message.avatar" alt="" class="avatar"/>

                    <div class="message-text">{{ message.content }}</div>

                    <div v-if="message.author_id !== this.user.id" class="like">
                      <div>
                        <i @click="likeCounter(index, message.id)" class='bx bxs-like icon_like'></i>
                        <i @click="dislikeCounter(index, message.id)" class='bx bxs-dislike icon_like'></i>
                      </div>
                      <div class="count_likes"> {{ message.likes }} </div>
                    </div>
                    <!-- @click="changeShow2"-->
                    <div v-if="message.author_id !== this.user.id && this.user.id === this.events.author_id"
                         class="end_sprint"

                         @click="openConfirmationModal(index)"
                    >
                      <i class='bx bxs-party icon_end_sprint'></i>
                    </div>

                    <img v-if="message.author_id === this.user.id" :src="message.avatar" alt="" class="avatar"/>
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

          <!-- Модальное окно подтверждения -->
          <div class="modal" v-if="showModal">
            <div class="modal-content">
              <div class="block_for_modal_text">
                <p class="text_for_modal_window">Finish the sprint?</p>
              </div>
              <div class="modal-buttons">
                <my-button class="btn_modal_window" @click="determineTheWinner">Yes</my-button>
                <my-button class="btn_modal_window" @click="closeModal">Сancel</my-button>
              </div>
            </div>
          </div>
        </div>
        <div v-else class="voting-chat2">
          <textarea
              name="message"
              rows="15" cols="50"
              class="textarea_form_for_sprint"
              v-model="sprintMessage"
              required
          >

          </textarea>
          <div class="container_for_btn">
            <my-button class="btn_complete_sprint" @click="finishImplementing(false)">Continue event</my-button>
            <my-button class="btn_complete_event" @click="finishImplementing(true)">Complete the event</my-button>
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
function formatDate(date) {
  const hrs0 = '0' + date.getUTCHours()
  const mins0 = '0' + date.getUTCMinutes()
  const secs0 = '0' + date.getUTCSeconds()
  const hrs = hrs0.substring(hrs0.length-2)
  const mins = mins0.substring(mins0.length-2)
  const secs = secs0.substring(secs0.length-2)
  return `${date.getUTCFullYear()}-${date.getUTCMonth() + 1}-${date.getUTCDate()} ${hrs}:${mins}:${secs}`
}
export default {
  components: {Sprint, MyButton },
  data() {
    const user = JSON.parse(localStorage.getItem('user'));

    return {
      user: user,
      events: {},
      descriptionVisible: false,
      show: true,
      show2: true,
      inputMessage: "",
      sprintMessage: "",
      eventMessages: {},
      ID: this.$route.params.id,
      sprints: [],
      sprints_id: 0,
      showModal: false,
      selectedIndex: null,
    }
  },
  async beforeMount() {
    try {
      const ev = await this.$api.events.getOne(this.ID);
      this.events = ev.data.event
      this.sprints = ev.data.sprints

      console.log("user", this.user)
      console.log("this.sprints", this.sprints)
      for (const sprint of this.sprints) {
        this.sprints_id = sprint.id
        console.log("id", sprint.id)

        break
      }

      try {
        console.log("filterSuggestion", this.sprints_id)
        const suggestions = await this.$api.suggestions.filterSuggestion({
          "filter": [
            [
              ["sprint_id", "=", this.sprints_id]
            ]
          ]
        });

        this.eventMessages[this.ID] = [];
        for (const entry of suggestions.data) {
          this.eventMessages[this.ID].push({
            id: entry.id,
            content: entry.post.text_content,
            sprint_id: entry.sprint_id,
            username: entry.author.username,
            avatar: entry.author.pfp_url,
            likes: entry.votes,
            author_id: entry.author_id,
          })
          const data = this.eventMessages[this.ID]

          console.log("suggestions", entry)
          console.log("this.messages", this.eventMessages[this.ID])

          if (data) {
            this.scrollToBottom();
          }
        }
      } catch (error) {
        console.log('failed:', error);
      }

      const storedMessages = localStorage.getItem('chatMessages');
      if (storedMessages) {
        this.eventMessages[this.ID] = JSON.parse(storedMessages);
      }

      this.scrollToBottom()
    } catch (error) {
      console.log('failed:', error);
    }
  },
  methods: {
    changeShow2() {
      this.show2 = !this.show2
    },
    async likeCounter(index, id) {
      const message = this.eventMessages[this.ID][index];
      if (message.likedByUser !== "like") {
        if (message.likedByUser === "dislike") {
          message.likes += 2; // Увеличиваем на 2, так как изначально уменьшалось на 1
        } else {
          message.likes += 1;
        }
        message.likedByUser = "like";
        localStorage.setItem('chatMessages', JSON.stringify(this.eventMessages[this.ID]));

        try {
          const response = await this.$api.suggestions.voteSuggestion(id, {
            vote_value: message.likes
          });

          console.log('Лайк успешно добавлен:', response.data);
        } catch (error) {
          console.error('Ошибка при добавлении лайка:', error);
        }
      }

      const iconLike = document.querySelectorAll('.icon_like');
      iconLike.forEach((icon, i) => {
        if (i === index) {
          icon.classList.add('active');
        } else {
          icon.classList.remove('active');
        }
      });
    },

    async dislikeCounter(index, id) {
      const message = this.eventMessages[this.ID][index];
      if (message.likedByUser !== "dislike") {
        if (message.likedByUser === "like") {
          message.likes -= 2; // Уменьшаем на 2, так как изначально увеличивалось на 1
        } else {
          message.likes -= 1;
        }
        message.likedByUser = "dislike";
        localStorage.setItem('chatMessages', JSON.stringify(this.eventMessages[this.ID]));

        try {
          const response = await this.$api.suggestions.voteSuggestion(id, {
            vote_value: message.likes
          });

          console.log('Дизлайк успешно добавлен:', response.data);
        } catch (error) {
          console.error('Ошибка при добавлении дизлайка:', error);
        }
      }

      const iconDislike = document.querySelectorAll('.icon_dislike');
      iconDislike.forEach((icon, i) => {
        if (i === index) {
          icon.classList.add('active');
        } else {
          icon.classList.remove('active');
        }
      });
    },
    getMessageClasses(message, user) {
      return {
        'message-right': message.username === user.username,
        'message-left': message.username !== user.username,
      };
    },
    toggleDescription() {
      this.descriptionVisible = !this.descriptionVisible;
    },
    Show() {
      this.show = !this.show;
    },
    scrollToBottom() {
      this.$nextTick(() => {
        const messageContainer = this.$refs.messageContainer;
        if (messageContainer) {
          messageContainer.scrollTop = messageContainer.scrollHeight;
        }
      });
    },
    async SendMessage() {
      try {
        if (this.inputMessage === "" || this.inputMessage === null) {
          return;
        }

        if (!this.eventMessages[this.ID]) {
          this.eventMessages[this.ID] = [];
        }

        const response = await this.$api.suggestions.createSuggestion({
          suggestion: {sprint_id: this.sprints_id},
          content: {text_content: this.inputMessage}
        })

        this.eventMessages[this.ID].push({
          id: response.data.id,
          author_id: this.user.id,
          content: this.inputMessage,
          username: this.user.username,
          avatar: this.user.pfp_url,
          likes: 0,
          sprint_id: this.sprint_id,
        });

        localStorage.setItem('chatMessages', JSON.stringify(this.eventMessages[this.ID]));

        this.inputMessage = "";
        console.log('Сообщение успешно создано:', response)

        this.scrollToBottom();

        console.log("message", this.messages)
      } catch (error) {
        console.error('Ошибка при создании сообщения:', error)
      }
    },
    async determineTheWinner() {
      if (this.selectedIndex !== null) {
        this.changeShow2();
        this.closeModal();

        try {
          const response = await this.$api.events.finishVoting(this.ID, {
            suggestion_winner_id: [this.selectedIndex]
          })
          this.sprintMessage = "";

          console.log('Победитель успешно выбран:', response.data)
          this.show2 = !this.show2
        } catch (error) {
          console.error('Ошибка при определении победителя:', error)
        }
      }
    },
    async finishImplementing(bool) {
      try {
        const response = await this.$api.events.finishImplementingEvent(this.ID, {
          content: {text_content: this.sprintMessage},
          is_last_sprint: bool
        })
        this.sprintMessage = "";

        console.log('Спринт успешно создан:', response.data)
        this.show2 = !this.show2
      } catch (error) {
        console.error('Ошибка при создании спринта:', error)
      }

      try {
        const ev = await this.$api.events.getOne(this.ID);
        this.events = ev.data.event
        this.sprints = ev.data.sprints

        for (const sprint of this.sprints) {
          this.sprints_id = sprint.id
        }
      } catch (error) {
        console.log('failed:', error);
      }
    },
    openConfirmationModal(index) {
      this.selectedIndex = index;
      this.showModal = true;
    },

    closeModal() {
      this.showModal = false;
      this.selectedIndex = null;
    },

  },
  async mounted() {

  },
}
</script>

<style scoped>
@import "@/styles.css";
.icon_like.active {
  color: #31a0a8; /* Цвет для активного лайка */
}

.icon_dislike.active {
  color: #31a0a8; /* Цвет для активного дизлайка */
}

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
  top: 0;
  border: 2px solid var(--border-light-gray-color);
  border-radius: 5px;
  width: 25%;
  height: 80vh;

  display: flex;
  flex-direction: column;
  //align-items: center;
}

.container-for-sprints {
  //position: absolute;
  overflow-y: auto;
  width: 100%;
  height: calc(100% - 40px);
  margin-top: 40px;
  padding-top: 40px;
}

.container-for-sprints::-webkit-scrollbar {
  width: 0;
  height: 0;
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
  background-color: var(--message-green-color);
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


/* Стили для модального окна */
.modal {
  position: fixed;
  z-index: 999;
  left: 0;
  top: 0;
  width: 100%;
  height: 100%;
  background-color: rgba(0, 0, 0, 0.5);
  display: flex;
  justify-content: center;
  align-items: center;
}

.modal-content {
  background-color: var(--navbar-color);
  padding: 20px;
  border-radius: 5px;

}

.block_for_modal_text {
  width: 100%;
  display: flex;
  justify-content: center;
}

.text_for_modal_window {
  font-size: 18px;
  color: var(--text-wight-color);
}

.modal-buttons {
  display: flex;
  justify-content: space-between;
  margin-top: 20px;
}

.btn_modal_window {
  width: 100px;
  height: 30px;
  border: none;
  border-radius: 5px;
  font-weight: 300;
  justify-content: center;
  align-items: center;
  color: var(--text-wight-color);
  font-size: 16px;
  margin-right: 10px;
}

.btn_modal_window:last-child {
  margin-right: 0;
  margin-left: 10px;
}
</style>